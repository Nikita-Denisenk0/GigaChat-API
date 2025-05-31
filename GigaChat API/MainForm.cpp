#include "MainForm.h"
#include <iostream>
#include <msclr/marshal_cppstd.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <vector>

using namespace msclr::interop;
using namespace GigaChatAPI;
using namespace System::Windows::Forms;
using namespace System::Text;
using namespace System::Drawing;

std::vector<nlohmann::json> messageHistory; // История сообщений для поддержки контекста диалога

// Генерация UUID для запросов
std::string generate_uuid() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> section4(0, 0x0FFF);
    std::uniform_int_distribution<uint16_t> section3(0, 0x3FFF);
    std::uniform_int_distribution<uint64_t> section5(0, 0xFFFFFFFFFFFF);

    std::stringstream uuid;
    uuid.imbue(std::locale::classic());
    uuid << std::hex << std::setfill('0');

    uuid << std::setw(8) << (gen() & 0xFFFFFFFF) << "-";
    uuid << std::setw(4) << (gen() & 0xFFFF) << "-";
    uuid << "4" << std::setw(3) << (section4(gen) & 0x0FFF) << "-";
    uuid << std::setw(4) << (0x8000 | (section3(gen) & 0x3FFF)) << "-";
    uuid << std::setw(12) << section5(gen);

    return uuid.str();
}

// Callback-функция для записи ответа от CURL
static size_t write_callback(void* data, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)data, size * nmemb);
    return size * nmemb;
}

// Получение токена доступа для API GigaChat
std::string get_access_token() {
    const std::string CLIENT_SECRET = "MjU5Y2I5NTEtOGQ1YS00ODQzLWFhZmEtNWIyNzIyYTY1YmM0OmQ2OTIxMDY0LTdiYzEtNDY4Yy1hYzRmLTYyMzg2MWMwODljOQ==";
    const std::string OAUTH_URL = "https://ngw.devices.sberbank.ru:9443/api/v2/oauth";
    const std::string SCOPE = "GIGACHAT_API_PERS";

    CURL* curl = curl_easy_init();
    std::string response;

    if (!curl) return "";

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    headers = curl_slist_append(headers, ("Authorization: Basic " + CLIENT_SECRET).c_str());
    headers = curl_slist_append(headers, ("RqUID: " + generate_uuid()).c_str());

    const std::string data = "scope=" + SCOPE + "&grant_type=client_credentials";

    curl_easy_setopt(curl, CURLOPT_URL, OAUTH_URL.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    CURLcode result = curl_easy_perform(curl);
    long http_code = 400;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    if (result != CURLE_OK || http_code != 200) {
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return "";
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    try {
        nlohmann::json token_data = nlohmann::json::parse(response);
        return token_data.value("access_token", "");
    }
    catch (...) {
        return "";
    }
}

// Отправка запроса в GigaChat с учетом контекста
std::string query_gigachat(const std::string& prompt, const std::string& token) {
    const std::string API_URL = "https://gigachat.devices.sberbank.ru/api/v1/chat/completions";
    if (token.empty()) return "";

    // Добавляем новый запрос в историю
    messageHistory.push_back({ {"role", "user"}, {"content", prompt} });

    CURL* curl = curl_easy_init();
    std::string response;
    if (!curl) return "";

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());

    nlohmann::json request = {
        {"model", "GigaChat:latest"},
        {"messages", messageHistory},
        {"temperature", 0.7}
    };

    const std::string json_data = request.dump();

    curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    CURLcode result = curl_easy_perform(curl);
    long http_code = 400;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    if (result != CURLE_OK || http_code != 200) {
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return "";
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    try {
        nlohmann::json response_data = nlohmann::json::parse(response);
        std::string answer = response_data["choices"][0]["message"]["content"].get<std::string>();

        // Добавляем ответ в историю и ограничиваем размер
        messageHistory.push_back({ {"role", "assistant"}, {"content", answer} });
        if (messageHistory.size() > 6) {
            messageHistory.erase(messageHistory.begin(), messageHistory.begin() + 2);
        }

        return answer;
    }
    catch (...) {
        return "";
    }
}

// Конвертация System::String^ в UTF-8
std::string ConvertToUTF8(System::String^ input) {
    array<unsigned char>^ bytes = Encoding::UTF8->GetBytes(input);
    pin_ptr<unsigned char> pinned = &bytes[0];
    return std::string(reinterpret_cast<char*>(pinned), bytes->Length);
}

// Конвертация UTF-8 в System::String^
System::String^ ConvertFromUTF8(const std::string& input) {
    array<unsigned char>^ bytes = gcnew array<unsigned char>(static_cast<int>(input.size()));
    for (size_t i = 0; i < input.size(); ++i)
        bytes[i] = input[i];
    return Encoding::UTF8->GetString(bytes);
}

// Добавление сообщений с форматированием в историю чата
void AddMessageToHistory(RichTextBox^ outputField, System::String^ message, bool isUser) {
    Color textColor = isUser ? Color::FromArgb(74, 108, 247) : Color::FromArgb(31, 41, 55);
    String^ prefix = isUser ? "[Вы] " : "[GigaChat] ";

    // Установка стиля для префикса (жирный)
    outputField->SelectionStart = outputField->TextLength;
    outputField->SelectionColor = textColor;
    outputField->SelectionFont = gcnew System::Drawing::Font("Segoe UI", 10.8F, FontStyle::Bold);
    outputField->AppendText(prefix);

    // Установка стиля для основного текста (обычный)
    outputField->SelectionStart = outputField->TextLength;
    outputField->SelectionColor = Color::FromArgb(75, 85, 99);
    outputField->SelectionFont = gcnew System::Drawing::Font("Segoe UI", 10.8F);
    outputField->AppendText(message + "\n\n");

    // Автоматическая прокрутка к последнему сообщению
    outputField->SelectionStart = outputField->TextLength;
    outputField->ScrollToCaret();
}

// Обработчик кнопки отправки сообщения
System::Void MainForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Проверка на пустое сообщение
        if (inputField->Text == "Введите ваш запрос..." || String::IsNullOrWhiteSpace(inputField->Text)) {
            MessageBox::Show("Введите текст вашего запроса!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        std::string prompt = ConvertToUTF8(inputField->Text);

        // Добавляем сообщение пользователя в историю
        AddMessageToHistory(outputField, inputField->Text, true);

        // Показываем индикатор печати
        statusLabel->Text = "GigaChat печатает...";
        dotCount = 0;
        inputField->Clear();
        typingTimer->Start();
        Application::DoEvents(); // Принудительное обновление UI

        // Получение токена доступа
        std::string token = get_access_token();
        if (token.empty()) {
            typingTimer->Stop();
            MessageBox::Show("Не удалось получить токен! Проверьте интернет соединение!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            statusLabel->Text = "Ошибка авторизации";
            return;
        }

        // Отправка запроса в GigaChat API
        std::string response = query_gigachat(prompt, token);
        if (response.empty()) {
            typingTimer->Stop();
            MessageBox::Show("Ошибка получения ответа!", "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            statusLabel->Text = "Ошибка получения ответа";
            return;
        }

        // Добавляем ответ в историю
        typingTimer->Stop();
        statusLabel->Text = "Готов к работе";
        AddMessageToHistory(outputField, ConvertFromUTF8(response), false);
    }
    catch (const std::exception& ex) {
        typingTimer->Stop();
        MessageBox::Show(gcnew System::String(ex.what()), "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        statusLabel->Text = "Ошибка: " + gcnew System::String(ex.what());
    }
    catch (...) {
        typingTimer->Stop();
        MessageBox::Show("Неизвестная ошибка!", "Ошибка",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        statusLabel->Text = "Неизвестная ошибка";
    }
}

// Инициализация при загрузке формы
System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
    curl_global_init(CURL_GLOBAL_DEFAULT); // Инициализация CURL
    inputField->Text = "Введите ваш запрос...";
    inputField->ForeColor = Color::FromArgb(156, 163, 175); // Серый цвет плейсхолдера
    outputField->BackColor = Color::FromArgb(249, 250, 251); // Светлый фон истории
}

// Очистка ресурсов при закрытии формы
System::Void MainForm::MainForm_FormClosing(System::Object^ sender, FormClosingEventArgs^ e) {
    curl_global_cleanup(); // Очистка CURL
}

// Обработчик получения фокуса полем ввода
System::Void MainForm::inputField_Enter(System::Object^ sender, System::EventArgs^ e) {
    // Очистка плейсхолдера
    if (inputField->Text == "Введите ваш запрос...") {
        inputField->Text = "";
        inputField->ForeColor = SystemColors::WindowText; // Стандартный цвет текста
    }
}

// Обработчик потери фокуса полем ввода
System::Void MainForm::inputField_Leave(System::Object^ sender, System::EventArgs^ e) {
    // Восстановление плейсхолдера
    if (String::IsNullOrWhiteSpace(inputField->Text)) {
        inputField->Text = "Введите ваш запрос...";
        inputField->ForeColor = Color::FromArgb(156, 163, 175); // Серый цвет
    }
}

// Обработчик нажатия клавиш в поле ввода
System::Void MainForm::inputField_KeyDown(System::Object^ sender, KeyEventArgs^ e) {
    // Отправка сообщения по Enter (без Shift)
    if (e->KeyCode == Keys::Enter && !e->Shift) {
        e->SuppressKeyPress = true; // Предотвращаем звук системы
        button1_Click(sender, e);   // Вызов обработчика отправки
    }
}

// Обработчик тика таймера для анимации печати
System::Void MainForm::typingTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
    dotCount = (dotCount % 3) + 1; // Цикл 1-2-3
    statusLabel->Text = "GigaChat печатает" + gcnew String('.', dotCount);
}

// Очистка истории сообщений
System::Void MainForm::clearButton_Click(System::Object^ sender, System::EventArgs^ e) {
    outputField->Clear();
    messageHistory.clear();
    statusLabel->Text = "История очищена";
}

// Точка входа приложения
[STAThread]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew GigaChatAPI::MainForm());
    return 0;
}
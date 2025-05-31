#pragma once

namespace GigaChatAPI {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Text;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();
            this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private:
        // Элементы управления формы
        System::Windows::Forms::Button^ sendbutton;         // Кнопка отправки сообщения
        System::Windows::Forms::Panel^ panel1;              // Верхняя панель с заголовком
        System::Windows::Forms::Label^ label1;              // Заголовок приложения
        System::Windows::Forms::RichTextBox^ outputField;   // Поле вывода сообщений
        System::Windows::Forms::RichTextBox^ inputField;    // Поле ввода сообщений
        System::Windows::Forms::StatusStrip^ statusBar;     // Строка состояния
        System::Windows::Forms::ToolStripStatusLabel^ statusLabel; // Элемент статуса
        System::Windows::Forms::Timer^ typingTimer;         // Таймер для анимации печати
        int dotCount;                                       // Счетчик точек для анимации печати
        System::Windows::Forms::Panel^ inputPanel;          // Панель для поля ввода и кнопок
        System::Windows::Forms::Button^ clearButton;        // Кнопка очистки истории

    private: System::ComponentModel::IContainer^ components; // Контейнер компонентов

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->components = (gcnew System::ComponentModel::Container());
               System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
               this->sendbutton = (gcnew System::Windows::Forms::Button());
               this->panel1 = (gcnew System::Windows::Forms::Panel());
               this->label1 = (gcnew System::Windows::Forms::Label());
               this->outputField = (gcnew System::Windows::Forms::RichTextBox());
               this->inputField = (gcnew System::Windows::Forms::RichTextBox());
               this->statusBar = (gcnew System::Windows::Forms::StatusStrip());
               this->statusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
               this->typingTimer = (gcnew System::Windows::Forms::Timer(this->components));
               this->inputPanel = (gcnew System::Windows::Forms::Panel());
               this->clearButton = (gcnew System::Windows::Forms::Button());
               this->panel1->SuspendLayout();
               this->statusBar->SuspendLayout();
               this->inputPanel->SuspendLayout();
               this->SuspendLayout();
               // 
               // sendbutton
               // 
               this->sendbutton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(108)),
                   static_cast<System::Int32>(static_cast<System::Byte>(247)));
               this->sendbutton->Cursor = System::Windows::Forms::Cursors::Hand;
               this->sendbutton->Dock = System::Windows::Forms::DockStyle::Right;
               this->sendbutton->FlatAppearance->BorderSize = 0;
               this->sendbutton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->sendbutton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(204)));
               this->sendbutton->ForeColor = System::Drawing::Color::White;
               this->sendbutton->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
               this->sendbutton->Location = System::Drawing::Point(982, 10);
               this->sendbutton->Name = L"sendbutton";
               this->sendbutton->Size = System::Drawing::Size(120, 40);
               this->sendbutton->TabIndex = 0;
               this->sendbutton->Text = L"Отправить";
               this->sendbutton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
               this->sendbutton->UseVisualStyleBackColor = false;
               this->sendbutton->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
               // 
               // panel1
               // 
               this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(108)),
                   static_cast<System::Int32>(static_cast<System::Byte>(247)));
               this->panel1->Controls->Add(this->label1);
               this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
               this->panel1->Location = System::Drawing::Point(0, 0);
               this->panel1->Name = L"panel1";
               this->panel1->Size = System::Drawing::Size(1122, 60);
               this->panel1->TabIndex = 0;
               // 
               // label1
               // 
               this->label1->AutoSize = true;
               this->label1->Dock = System::Windows::Forms::DockStyle::Left;
               this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(204)));
               this->label1->ForeColor = System::Drawing::Color::White;
               this->label1->Location = System::Drawing::Point(0, 0);
               this->label1->Name = L"label1";
               this->label1->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
               this->label1->Size = System::Drawing::Size(303, 41);
               this->label1->TabIndex = 0;
               this->label1->Text = L"GigaChat Assistant";
               // 
               // outputField
               // 
               this->outputField->BackColor = System::Drawing::Color::White;
               this->outputField->BorderStyle = System::Windows::Forms::BorderStyle::None;
               this->outputField->Dock = System::Windows::Forms::DockStyle::Fill;
               this->outputField->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(204)));
               this->outputField->Location = System::Drawing::Point(0, 60);
               this->outputField->Margin = System::Windows::Forms::Padding(20);
               this->outputField->Name = L"outputField";
               this->outputField->ReadOnly = true;
               this->outputField->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
               this->outputField->Size = System::Drawing::Size(1122, 527);
               this->outputField->TabIndex = 1;
               this->outputField->Text = L"";
               this->outputField->TextChanged += gcnew System::EventHandler(this, &MainForm::outputField_TextChanged);
               // 
               // inputField
               // 
               this->inputField->BackColor = System::Drawing::Color::White;
               this->inputField->BorderStyle = System::Windows::Forms::BorderStyle::None;
               this->inputField->Dock = System::Windows::Forms::DockStyle::Fill;
               this->inputField->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(204)));
               this->inputField->Location = System::Drawing::Point(20, 10);
               this->inputField->Margin = System::Windows::Forms::Padding(20);
               this->inputField->Name = L"inputField";
               this->inputField->Size = System::Drawing::Size(962, 40);
               this->inputField->TabIndex = 0;
               this->inputField->Text = L"Введите ваш запрос...";
               this->inputField->Enter += gcnew System::EventHandler(this, &MainForm::inputField_Enter);
               this->inputField->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::inputField_KeyDown);
               this->inputField->Leave += gcnew System::EventHandler(this, &MainForm::inputField_Leave);
               // 
               // statusBar
               // 
               this->statusBar->BackColor = System::Drawing::Color::White;
               this->statusBar->ImageScalingSize = System::Drawing::Size(20, 20);
               this->statusBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->statusLabel });
               this->statusBar->Location = System::Drawing::Point(0, 647);
               this->statusBar->Name = L"statusBar";
               this->statusBar->Size = System::Drawing::Size(1122, 26);
               this->statusBar->TabIndex = 2;
               this->statusBar->Text = L"statusStrip1";
               // 
               // statusLabel
               // 
               this->statusLabel->Name = L"statusLabel";
               this->statusLabel->Size = System::Drawing::Size(112, 20);
               this->statusLabel->Text = L"Готов к работе";
               // 
               // typingTimer
               // 
               this->typingTimer->Interval = 300;
               this->typingTimer->Tick += gcnew System::EventHandler(this, &MainForm::typingTimer_Tick);
               // 
               // inputPanel
               // 
               this->inputPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(244)),
                   static_cast<System::Int32>(static_cast<System::Byte>(255)));
               this->inputPanel->Controls->Add(this->clearButton);
               this->inputPanel->Controls->Add(this->inputField);
               this->inputPanel->Controls->Add(this->sendbutton);
               this->inputPanel->Dock = System::Windows::Forms::DockStyle::Bottom;
               this->inputPanel->Location = System::Drawing::Point(0, 587);
               this->inputPanel->Name = L"inputPanel";
               this->inputPanel->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
               this->inputPanel->Size = System::Drawing::Size(1122, 60);
               this->inputPanel->TabIndex = 3;
               // 
               // clearButton
               // 
               this->clearButton->BackColor = System::Drawing::Color::White;
               this->clearButton->Cursor = System::Windows::Forms::Cursors::Hand;
               this->clearButton->Dock = System::Windows::Forms::DockStyle::Right;
               this->clearButton->FlatAppearance->BorderSize = 0;
               this->clearButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->clearButton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(204)));
               this->clearButton->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(100)), static_cast<System::Int32>(static_cast<System::Byte>(116)),
                   static_cast<System::Int32>(static_cast<System::Byte>(139)));
               this->clearButton->Location = System::Drawing::Point(862, 10);
               this->clearButton->Name = L"clearButton";
               this->clearButton->Size = System::Drawing::Size(120, 40);
               this->clearButton->TabIndex = 2;
               this->clearButton->Text = L"Очистить";
               this->clearButton->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
               this->clearButton->UseVisualStyleBackColor = false;
               this->clearButton->Click += gcnew System::EventHandler(this, &MainForm::clearButton_Click);
               // 
               // MainForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(9, 23);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::White;
               this->ClientSize = System::Drawing::Size(1122, 673);
               this->Controls->Add(this->outputField);
               this->Controls->Add(this->inputPanel);
               this->Controls->Add(this->panel1);
               this->Controls->Add(this->statusBar);
               this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                   static_cast<System::Byte>(204)));
               this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
               this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->MinimumSize = System::Drawing::Size(800, 600);
               this->Name = L"MainForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"GigaChat ";
               this->panel1->ResumeLayout(false);
               this->panel1->PerformLayout();
               this->statusBar->ResumeLayout(false);
               this->statusBar->PerformLayout();
               this->inputPanel->ResumeLayout(false);
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

    private:
        // Обработчики событий
        System::Void button1_Click(System::Object^ sender, System::EventArgs^ e); // Отправка сообщения
        System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);   // Загрузка формы
        System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e); // Закрытие формы

        // Работа с полем ввода
        System::Void inputField_Enter(System::Object^ sender, System::EventArgs^ e);    // Фокус на поле ввода
        System::Void inputField_Leave(System::Object^ sender, System::EventArgs^ e);    // Потеря фокуса полем ввода
        System::Void inputField_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e); // Обработка нажатия клавиш

        // Таймер и дополнительные функции
        System::Void typingTimer_Tick(System::Object^ sender, System::EventArgs^ e);    // Тик таймера для анимации печати
        System::Void clearButton_Click(System::Object^ sender, System::EventArgs^ e);   // Очистка истории сообщений

    private:
        // Обработчик изменения текста в поле вывода
        System::Void outputField_TextChanged(System::Object^ sender, System::EventArgs^ e) {
        }
    };
}
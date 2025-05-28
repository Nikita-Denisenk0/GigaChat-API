#pragma once
#pragma execution_character_set("utf-8")

namespace GigaChatAPI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
	private: System::Windows::Forms::Button^ sendbutton;
	protected:
	private:




	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::SplitContainer^ splitContainer1;
	private: System::Windows::Forms::RichTextBox^ outputField;

	private: System::Windows::Forms::RichTextBox^ inputField;






	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->sendbutton = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->outputField = (gcnew System::Windows::Forms::RichTextBox());
			this->inputField = (gcnew System::Windows::Forms::RichTextBox());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->SuspendLayout();
			// 
			// sendbutton
			// 
			this->sendbutton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(212)));
			this->sendbutton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->sendbutton->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->sendbutton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->sendbutton->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->sendbutton->ForeColor = System::Drawing::Color::White;
			this->sendbutton->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->sendbutton->Location = System::Drawing::Point(0, 628);
			this->sendbutton->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->sendbutton->Name = L"sendbutton";
			this->sendbutton->Size = System::Drawing::Size(1262, 45);
			this->sendbutton->TabIndex = 4;
			this->sendbutton->Text = L"🚀 Отправить";
			this->sendbutton->UseVisualStyleBackColor = false;
			this->sendbutton->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(212)));
			this->panel1->Controls->Add(this->label1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1262, 50);
			this->panel1->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Dock = System::Windows::Forms::DockStyle::Left;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->label1->Size = System::Drawing::Size(285, 41);
			this->label1->TabIndex = 0;
			this->label1->Text = L"GigaChat Assistant";
			this->label1->Click += gcnew System::EventHandler(this, &MainForm::label1_Click);
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 50);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->outputField);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->inputField);
			this->splitContainer1->Size = System::Drawing::Size(1262, 578);
			this->splitContainer1->SplitterDistance = 537;
			this->splitContainer1->TabIndex = 6;
			// 
			// outputField
			// 
			this->outputField->BackColor = System::Drawing::Color::White;
			this->outputField->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->outputField->Dock = System::Windows::Forms::DockStyle::Fill;
			this->outputField->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->outputField->Location = System::Drawing::Point(0, 0);
			this->outputField->Margin = System::Windows::Forms::Padding(20, 20, 20, 0);
			this->outputField->Name = L"outputField";
			this->outputField->ReadOnly = true;
			this->outputField->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->outputField->Size = System::Drawing::Size(1262, 537);
			this->outputField->TabIndex = 4;
			this->outputField->Text = L"";
			this->outputField->TextChanged += gcnew System::EventHandler(this, &MainForm::outputField_TextChanged);
			// 
			// inputField
			// 
			this->inputField->BackColor = System::Drawing::Color::White;
			this->inputField->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->inputField->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->inputField->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->inputField->Location = System::Drawing::Point(0, 1);
			this->inputField->Margin = System::Windows::Forms::Padding(20, 0, 20, 20);
			this->inputField->Name = L"inputField";
			this->inputField->Size = System::Drawing::Size(1262, 36);
			this->inputField->TabIndex = 3;
			this->inputField->Text = L"Введите ваш запрос...";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 23);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(1262, 673);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->sendbutton);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"GigaChat Client";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
		System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

private: System::Void outputField_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
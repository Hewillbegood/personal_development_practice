#pragma once



namespace ATM_GH2005 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// DebugTools ժҪ
	/// </summary>
	public ref class DebugTools : public System::Windows::Forms::Form
	{
	public:
		DebugTools(void)
		{
			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
		/// </summary>
		~DebugTools()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button3;

	private:
		/// <summary>
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->button1->Location = System::Drawing::Point(12, 76);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(121, 38);
			this->button1->TabIndex = 0;
			this->button1->Text = L"��� 10 ���»�Ա";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Yes;
			this->button2->Location = System::Drawing::Point(12, 120);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(121, 38);
			this->button2->TabIndex = 1;
			this->button2->Text = L"��� 50 ������Ʒ.";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"΢���ź�", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(10, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(123, 64);
			this->label1->TabIndex = 2;
			this->label1->Text = L"����Ū��̫�鷳, �ַ�������ȷ��, ÿ���ַ����.";
			// 
			// button3
			// 
			this->button3->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button3->Location = System::Drawing::Point(12, 164);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(121, 38);
			this->button3->TabIndex = 3;
			this->button3->Text = L"����";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// DebugTools
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(145, 213);
			this->ControlBox = false;
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"DebugTools";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Debug Tools";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}

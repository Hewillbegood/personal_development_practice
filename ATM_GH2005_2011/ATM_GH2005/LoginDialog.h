#pragma once



namespace ATM_GH2005 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	// LoginDialog ժҪ
	public ref class LoginDialog : public System::Windows::Forms::Form
	{
	public:
		LoginDialog(void)
		{
			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
			//
			this->maskedTextBox1->Leave += gcnew EventHandler(this, &LoginDialog::MaskedTextBox1_Leave);
		}
	protected:
		// ������������ʹ�õ���Դ��
		~LoginDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::MaskedTextBox^  maskedTextBox2;
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::ComponentModel::IContainer^  components;
	protected: 
	private: // ����������������
	public: property LCP::LeaguerSuite^ LeaguerSuite0;

#pragma region Windows Form Designer generated code
		
		// �����֧������ķ��� - ��Ҫ
		// ʹ�ô���༭���޸Ĵ˷��������ݡ�
		
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginDialog::typeid));
			this->maskedTextBox1 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->maskedTextBox2 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// maskedTextBox1
			// 
			this->maskedTextBox1->BeepOnError = true;
			this->maskedTextBox1->Location = System::Drawing::Point(182, 47);
			this->maskedTextBox1->Mask = L"00LLLLLL";
			this->maskedTextBox1->Name = L"maskedTextBox1";
			this->maskedTextBox1->PromptChar = ' ';
			this->maskedTextBox1->Size = System::Drawing::Size(150, 33);
			this->maskedTextBox1->TabIndex = 0;
			this->maskedTextBox1->MaskInputRejected += gcnew System::Windows::Forms::MaskInputRejectedEventHandler(this, &LoginDialog::maskedTextBox1_MaskInputRejected);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"΢���ź�", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(79, 47);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(97, 33);
			this->label1->TabIndex = 1;
			this->label1->Text = L"�û�����";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"΢���ź�", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(79, 100);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(97, 33);
			this->label2->TabIndex = 3;
			this->label2->Text = L"�ܡ��룺";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label2->Click += gcnew System::EventHandler(this, &LoginDialog::label2_Click);
			// 
			// maskedTextBox2
			// 
			this->maskedTextBox2->Location = System::Drawing::Point(182, 101);
			this->maskedTextBox2->Name = L"maskedTextBox2";
			this->maskedTextBox2->Size = System::Drawing::Size(150, 33);
			this->maskedTextBox2->TabIndex = 2;
			this->maskedTextBox2->UseSystemPasswordChar = true;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"΢���ź�", 12.25F));
			this->button1->Location = System::Drawing::Point(84, 159);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(92, 32);
			this->button1->TabIndex = 4;
			this->button1->Text = L"ȷ��";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &LoginDialog::button1_Click);
			// 
			// button2
			// 
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button2->Font = (gcnew System::Drawing::Font(L"΢���ź�", 12.25F));
			this->button2->Location = System::Drawing::Point(240, 159);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(92, 32);
			this->button2->TabIndex = 5;
			this->button2->Text = L"����";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &LoginDialog::button2_Click);
			// 
			// LoginDialog
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->CancelButton = this->button2;
			this->ClientSize = System::Drawing::Size(428, 242);
			this->ControlBox = false;
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->maskedTextBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->maskedTextBox1);
			this->Font = (gcnew System::Drawing::Font(L"΢���ź�", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"LoginDialog";
			this->Opacity = 0.98;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"��Ա��½";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: 
		System::Void maskedTextBox1_MaskInputRejected(System::Object^ sender,
			System::Windows::Forms::MaskInputRejectedEventArgs^  e)
		{
			toolTip1->ToolTipTitle = "Invalid Input.";
			toolTip1->Show(L"�Բ��𣬺Ϸ����û�����ʽΪ��(Ӣ�İ��)�������֣�������Сд���ɵ���ĸ�����磬12BfiSuy��", 
				maskedTextBox1, Point(170, 0), 3000);
		}
	private: 
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if(maskedTextBox1->MaskCompleted == false)
			{
				toolTip1->ToolTipTitle = "Invalid Input.";
				toolTip1->Show(L"�Բ��𣬺Ϸ����û�����ʽΪ��(Ӣ�İ��)�������֣�������Сд���ɵ���ĸ�����磬12BfiSuy��", 
					maskedTextBox1, Point(170, 0), 3000);
				maskedTextBox1->Focus();
			}
			else
			{ 
/* 
SqlDataAdapter("SELECT * FROM dbo.CommodityInfo WHERE dbo.CommodityInfo.CommodityID=" + inInt.ToString(), gcnew SqlConnection("Data Source=127.0.0.1\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;"))),
			  stockDA(gcnew SqlDataAdapter("SELECT * FROM dbo.Stock WHERE dbo.Stock.CommodityID=" + inInt.ToString(), gcnew SqlConnection("Data Source=127.0.0.1\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;"))),
*/
				SqlDataAdapter^ tmpSqlDataAdapter = gcnew SqlDataAdapter( "SELECT * FROM dbo.Leaguer AS dl WHERE dl.UserID=\'" + maskedTextBox1->Text + "\' AND dl.PassWord=\'" + maskedTextBox2->Text + "\'", gcnew SqlConnection("Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;") );
				DataSet^ tmpDataSet = gcnew DataSet();
				int retrievedRowsAmount = tmpSqlDataAdapter->Fill(tmpDataSet, "Leaguer");
				if(retrievedRowsAmount == 1)
				{ // a final correct.
					this->LeaguerSuite0 = gcnew LCP::LeaguerSuite(tmpDataSet, tmpSqlDataAdapter);
					this->DialogResult = System::Windows::Forms::DialogResult::OK;
				}
				else
				{
					System::Media::SystemSounds::Exclamation->Play();
					MessageBox::Show(L"��������û�������������.");
					delete tmpSqlDataAdapter, tmpDataSet;
				}				
			}			
		}
	private: 
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
		{
		}
	private:
		void MaskedTextBox1_Leave(Object^ sender, EventArgs^ e)
		{
			if(maskedTextBox1->MaskCompleted == false)
			{
				toolTip1->ToolTipTitle = "Invalid Input.";
				toolTip1->Show(L"�Բ��𣬺Ϸ����û�����ʽΪ��(Ӣ�İ��)�������֣�������Сд���ɵ���ĸ�����磬12BfiSuy��",
					maskedTextBox1, Point(170, 0), 3000);
				maskedTextBox1->Focus();
			}
		}
	private: 
		System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) 
		{
		}
	};
}

#pragma once

namespace ATM_GH2005 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// 会员注册 摘要
	/// </summary>
	public ref class 会员注册 : public System::Windows::Forms::Form
	{
	public:
		会员注册(bool isStudent)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
			if( !isStudent )
			{
				this->label5->Enabled = false;
				this->label10->Enabled = false;
				this->textBox5->Enabled = false;
			}
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~会员注册()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(会员注册::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->ForeColor = System::Drawing::Color::Black;
			this->label1->Location = System::Drawing::Point(34, 87);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(69, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"用户　ID:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->ForeColor = System::Drawing::Color::Black;
			this->label2->Location = System::Drawing::Point(34, 139);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(68, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"姓　　名:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->ForeColor = System::Drawing::Color::Black;
			this->label3->Location = System::Drawing::Point(34, 191);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(68, 20);
			this->label3->TabIndex = 2;
			this->label3->Text = L"密　　码:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->ForeColor = System::Drawing::Color::Black;
			this->label4->Location = System::Drawing::Point(34, 243);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(68, 20);
			this->label4->TabIndex = 3;
			this->label4->Text = L"证件号码:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->ForeColor = System::Drawing::Color::Black;
			this->label5->Location = System::Drawing::Point(34, 295);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(68, 20);
			this->label5->TabIndex = 4;
			this->label5->Text = L"学校信息:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(109, 84);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(258, 26);
			this->textBox1->TabIndex = 5;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(109, 136);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(258, 26);
			this->textBox2->TabIndex = 6;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(109, 188);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(258, 26);
			this->textBox3->TabIndex = 7;
			this->textBox3->UseSystemPasswordChar = true;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(109, 240);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(258, 26);
			this->textBox4->TabIndex = 8;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(109, 292);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(258, 26);
			this->textBox5->TabIndex = 9;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->ForeColor = System::Drawing::Color::Black;
			this->label6->Location = System::Drawing::Point(105, 113);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(261, 20);
			this->label6->TabIndex = 10;
			this->label6->Text = L"格式: 两个数字 + 六个大小写均可的字母.";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::Transparent;
			this->label7->ForeColor = System::Drawing::Color::Black;
			this->label7->Location = System::Drawing::Point(105, 165);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(148, 20);
			this->label7->TabIndex = 11;
			this->label7->Text = L"最多可填写 15 个字符.";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->ForeColor = System::Drawing::Color::Black;
			this->label8->Location = System::Drawing::Point(105, 217);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(190, 20);
			this->label8->TabIndex = 12;
			this->label8->Text = L"最多可填写 10 个非中文字符.";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->ForeColor = System::Drawing::Color::Black;
			this->label9->Location = System::Drawing::Point(105, 269);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(190, 20);
			this->label9->TabIndex = 13;
			this->label9->Text = L"最多可填写 20 个非中文字符.";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->ForeColor = System::Drawing::Color::Black;
			this->label10->Location = System::Drawing::Point(105, 321);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(267, 20);
			this->label10->TabIndex = 14;
			this->label10->Text = L"注册学生会员专用, 最多可填写 15 个字符.";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(38, 387);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(120, 36);
			this->button1->TabIndex = 15;
			this->button1->Text = L"提交";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &会员注册::button1_Click);
			// 
			// button2
			// 
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button2->Location = System::Drawing::Point(246, 387);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(120, 36);
			this->button2->TabIndex = 16;
			this->button2->Text = L"放弃";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// label11
			// 
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->ForeColor = System::Drawing::Color::Black;
			this->label11->Location = System::Drawing::Point(34, 9);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(333, 43);
			this->label11->TabIndex = 17;
			this->label11->Text = L"懒于写验证代码了, 码农干的苦力不是一般的无聊.\r\n如果胡乱输入, 程序异常了, 不是我的毛病.";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::Transparent;
			this->label12->ForeColor = System::Drawing::Color::Black;
			this->label12->Location = System::Drawing::Point(34, 52);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(233, 20);
			this->label12->TabIndex = 18;
			this->label12->Text = L"一次性存入 500 元, 并填写以下表单.";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label13
			// 
			this->label13->BackColor = System::Drawing::Color::Transparent;
			this->label13->ForeColor = System::Drawing::Color::Red;
			this->label13->Location = System::Drawing::Point(34, 364);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(199, 20);
			this->label13->TabIndex = 19;
			// 
			// 会员注册
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->CausesValidation = false;
			this->ClientSize = System::Drawing::Size(409, 435);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"微软雅黑", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->MaximizeBox = false;
			this->Name = L"会员注册";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"会员注册";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: 
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			String^ idString = textBox1->Text;
			if( idString->Length == 8 && idString[0] >= '0' && idString[0] <= '9' && idString[1] >= '0' && idString[1] <= '9')
			{
				bool isOK = true;
				for( int i=0; i<6; i++ )
				{
					int p = i + 2;
					if( !((idString[p] >= 'A' && idString[p] <= 'Z') || (idString[p] >= 'a' && idString[p] <= 'z')) )
					{
						isOK = false;
					}
				}
				if(isOK)
				{
					SqlConnection^ conn = gcnew SqlConnection( "Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;" );
					conn->Open();
					SqlCommand^ cmd = conn->CreateCommand();
					cmd->CommandText = "SELECT * FROM dbo.Leaguer WHERE dbo.Leaguer.UserID=\'" + textBox1->Text + "\'";
					cmd->CommandType = CommandType::Text;
					SqlDataReader^ theDataReader = cmd->ExecuteReader();
					bool hasRows = theDataReader->HasRows;
					theDataReader->Close();
					// how to get correct effectedRows.
					if( ! hasRows )
					{
						String^ typeStr;
						String^ schoolStr;
						if( textBox5->Enabled == false )
						{
							typeStr = "Nor";
							schoolStr = "NULL";
						}
						else
						{
							typeStr = "Stu";
							schoolStr = "\'" + textBox5->Text + "\'";
						}
						cmd->CommandText = "INSERT INTO dbo.Leaguer VALUES(\'" + textBox1->Text + "\', N\'" + textBox2->Text
							+ "\', \'" + textBox3->Text + "\', \'" + textBox4->Text + "\', 50000, \'" + typeStr + "\', " + schoolStr + ")";
						cmd->ExecuteNonQuery();
						conn->Close();
						delete cmd;
						this->DialogResult = System::Windows::Forms::DialogResult::OK;
					}
					else
					{
						conn->Close();
						delete cmd;
						System::Media::SystemSounds::Exclamation->Play();
						label13->Text = L"用户 ID 已存在.";
					}
				}
				else
				{
					System::Media::SystemSounds::Exclamation->Play();
					label13->Text = L"用户 ID 格式不正确.";
				}
			}
			else
			{
				System::Media::SystemSounds::Exclamation->Play();
				label13->Text = L"用户 ID 格式不正确.";
			}
		}
	};
}

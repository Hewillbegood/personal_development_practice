#pragma once
#include "LoginDialog.h"
#include "PayPage.h"
#include "RecordQuery.h"
#include "CommodityEntering.h"
#include "Register.h"
#include "会员注册.h"
#include "DebugTools.h"

namespace ATM_GH2005 {

	// nullptr: empty trace handle.

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace LCP;

	// <summary>
	// Form1 摘要
	// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public: 
		Form1(void)
			: mousePos(Point(0,0)), leftMouseIsDown(false)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//form movement.
			//
			this->pictureBox1->MouseDown += gcnew MouseEventHandler(this, &Form1::PictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew MouseEventHandler(this, &Form1::PictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew MouseEventHandler(this, &Form1::PictureBox1_MouseUp);
			this->pictureBox2->MouseDown += gcnew MouseEventHandler(this, &Form1::PictureBox2_MouseDown);
			this->pictureBox2->MouseUp += gcnew MouseEventHandler(this, &Form1::PictureBox2_MouseUp);
			this->pictureBox3->MouseDown += gcnew MouseEventHandler(this, &Form1::PictureBox3_MouseDown);
			this->pictureBox3->MouseUp += gcnew MouseEventHandler(this, &Form1::PictureBox3_MouseUp);
			this->pictureBox6->MouseDown += gcnew MouseEventHandler(this, &Form1::PictureBox6_MouseDown);
			this->pictureBox6->MouseUp += gcnew MouseEventHandler(this, &Form1::PictureBox6_MouseUp);
			this->pictureBox7->MouseDown += gcnew MouseEventHandler(this, &Form1::PictureBox7_MouseDown);
			this->pictureBox7->MouseUp += gcnew MouseEventHandler(this, &Form1::PictureBox7_MouseUp);
			this->pictureBox8->MouseDown += gcnew MouseEventHandler(this, &Form1::PictureBox8_MouseDown);
			this->pictureBox8->MouseUp += gcnew MouseEventHandler(this, &Form1::PictureBox8_MouseUp);
			this->pictureBox9->MouseDown += gcnew MouseEventHandler(this, &Form1::PictureBox9_MouseDown);
			this->pictureBox9->MouseUp += gcnew MouseEventHandler(this, &Form1::PictureBox9_MouseUp);
			//
			// resources.
			//
			forForm1 = gcnew Resources::ResXResourceSet("ForForm1.resx");	
		}
	private: Resources::ResXResourceSet^ forForm1;
	private: Point mousePos;				//value field.
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::PictureBox^  pictureBox9;
	private: bool leftMouseIsDown;		//value field.
	private: 
		System::Void PictureBox1_MouseDown(Object^ sender, MouseEventArgs^ e)
		{
			mousePos = e->Location;
			if(e->Button == System::Windows::Forms::MouseButtons::Left) leftMouseIsDown = true;
		}
		System::Void PictureBox1_MouseMove(Object^ sender, MouseEventArgs^ e)
		{
			if(!leftMouseIsDown) return;
			this->Location = Point(this->Location.X + e->X - mousePos.X, this->Location.Y + e->Y - mousePos.Y);
		}
		System::Void PictureBox1_MouseUp(Object^ sender, MouseEventArgs^ e)
		{
			leftMouseIsDown = false;
		}
		System::Void PictureBox2_MouseDown(Object^ sender, MouseEventArgs^ e)
		{
			if(e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				leftMouseIsDown = true;
				this->pictureBox2->Image = (Bitmap^)forForm1->GetObject("NotLeaguerDown");
			}
		}
		System::Void PictureBox2_MouseUp(Object^ sender, MouseEventArgs^ e)
		{
			leftMouseIsDown = false;
			this->pictureBox2->Image = (Bitmap^)forForm1->GetObject("NotLeaguerUp");
		}
		System::Void PictureBox3_MouseDown(Object^ sender, MouseEventArgs^ e)
		{
			if(e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				leftMouseIsDown = true;
				this->pictureBox3->Image = (Bitmap^)forForm1->GetObject("LeaguerDown");
			}
		}
		System::Void PictureBox3_MouseUp(Object^ sender, MouseEventArgs^ e)
		{
			leftMouseIsDown = false;
			this->pictureBox3->Image = (Bitmap^)forForm1->GetObject("LeaguerUp");
		}
		System::Void PictureBox6_MouseDown(Object^ sender, MouseEventArgs^ e)
		{
			if(e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				leftMouseIsDown = true;
				this->pictureBox6->Image = (Bitmap^)forForm1->GetObject("QueryDown");
			}
		}
		System::Void PictureBox6_MouseUp(Object^ sender, MouseEventArgs^ e)
		{
			leftMouseIsDown = false;
			this->pictureBox6->Image = (Bitmap^)forForm1->GetObject("QueryUp");
		}
		System::Void PictureBox7_MouseDown(Object^ sender, MouseEventArgs^ e)
		{
			if(e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				leftMouseIsDown = true;
				this->pictureBox7->Image = (Bitmap^)forForm1->GetObject("RegisterDown");
			}
		}
		System::Void PictureBox7_MouseUp(Object^ sender, MouseEventArgs^ e)
		{
			leftMouseIsDown = false;
			this->pictureBox7->Image = (Bitmap^)forForm1->GetObject("RegisterUp");
		}
		System::Void PictureBox8_MouseDown(Object^ sender, MouseEventArgs^ e)
		{
			if(e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				leftMouseIsDown = true;
				this->pictureBox8->Image = (Bitmap^)forForm1->GetObject("quitDown");
			}
		}
		System::Void PictureBox8_MouseUp(Object^ sender, MouseEventArgs^ e)
		{
			leftMouseIsDown = false;
			this->pictureBox8->Image = (Bitmap^)forForm1->GetObject("quitUp");
		}
		System::Void PictureBox9_MouseDown(Object^ sender, MouseEventArgs^ e)
		{
			if(e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				leftMouseIsDown = true;
				this->pictureBox9->Image = (Bitmap^)forForm1->GetObject("DebugToolsDown");
			}
		}
		System::Void PictureBox9_MouseUp(Object^ sender, MouseEventArgs^ e)
		{
			leftMouseIsDown = false;
			this->pictureBox9->Image = (Bitmap^)forForm1->GetObject("DebugToolsUp");
		}
	protected:
		// <summary>
		// 清理所有正在使用的资源。
		// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected: 
	private:
		// <summary>
		// 必需的设计器变量。
		// </summary>
		System::ComponentModel::Container^components;

#pragma region Windows Form Designer generated code
		// <summary>
		// 设计器支持所需的方法 - 不要
		// 使用代码编辑器修改此方法的内容。
		// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox9))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			resources->ApplyResources(this->pictureBox1, L"pictureBox1");
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			resources->ApplyResources(this->pictureBox2, L"pictureBox2");
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &Form1::pictureBox2_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Transparent;
			resources->ApplyResources(this->pictureBox3, L"pictureBox3");
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &Form1::pictureBox3_Click);
			// 
			// pictureBox4
			// 
			resources->ApplyResources(this->pictureBox4, L"pictureBox4");
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox5
			// 
			resources->ApplyResources(this->pictureBox5, L"pictureBox5");
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->TabStop = false;
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->BackColor = System::Drawing::Color::White;
			this->label1->Name = L"label1";
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackColor = System::Drawing::Color::Transparent;
			resources->ApplyResources(this->pictureBox6, L"pictureBox6");
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->TabStop = false;
			this->pictureBox6->Click += gcnew System::EventHandler(this, &Form1::pictureBox6_Click);
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackColor = System::Drawing::Color::Transparent;
			resources->ApplyResources(this->pictureBox7, L"pictureBox7");
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->TabStop = false;
			this->pictureBox7->Click += gcnew System::EventHandler(this, &Form1::pictureBox7_Click);
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackColor = System::Drawing::Color::Transparent;
			resources->ApplyResources(this->pictureBox8, L"pictureBox8");
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->TabStop = false;
			this->pictureBox8->Click += gcnew System::EventHandler(this, &Form1::pictureBox8_Click);
			// 
			// pictureBox9
			// 
			this->pictureBox9->BackColor = System::Drawing::Color::Transparent;
			resources->ApplyResources(this->pictureBox9, L"pictureBox9");
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->TabStop = false;
			this->pictureBox9->Click += gcnew System::EventHandler(this, &Form1::pictureBox9_Click);
			// 
			// Form1
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->pictureBox9);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Form1";
			this->Opacity = 0.98;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox9))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void pictureBox2_Click(System::Object^ sender, System::EventArgs^ e) 
		{ // dealing, not leaguer.
			SqlDataAdapter^ tmpSqlDataAdapter = gcnew SqlDataAdapter( "SELECT * FROM dbo.Leaguer AS dl WHERE dl.UserID=\'00NopeCC\' AND dl.PassWord=\'Nope\'", gcnew SqlConnection("Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;") );
			DataSet^ tmpDataSet = gcnew DataSet();
			//
			// don't forget to rename a DataTable.
			//
			tmpSqlDataAdapter->Fill(tmpDataSet, "Leaguer");
			LCP::LeaguerSuite^ tmpLeaguerSuite = gcnew LCP::LeaguerSuite(tmpDataSet, tmpSqlDataAdapter);
			CommodityEntering^ theCommEntrng = gcnew CommodityEntering(tmpLeaguerSuite);
			this->Hide();
			if(theCommEntrng->ShowDialog(this) == System::Windows::Forms::DialogResult::Cancel)
			{
				delete theCommEntrng;
				this->Show();
			}
			else
			{
				delete theCommEntrng;
				this->Show();
			}
		}
		// forms control unexpectedly divided into two. 
	private: 
		System::Void pictureBox3_Click(System::Object^ sender, System::EventArgs^ e) 
		{ // leaguer.
			LoginDialog^ theLoginDialog = gcnew LoginDialog();
			if(theLoginDialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
			{
				CommodityEntering^ theCommEntrng = gcnew CommodityEntering(theLoginDialog->LeaguerSuite0);
				this->Hide();
				if(theCommEntrng->ShowDialog(this) == System::Windows::Forms::DialogResult::Cancel)
				{
					delete theCommEntrng;
					this->Show();
				}
				else
				{
					delete theCommEntrng;
					this->Show();
				}
			}
			delete theLoginDialog;
		}
	private: 
		System::Void pictureBox6_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			LoginDialog^ theLoginDialog = gcnew LoginDialog();
			if(theLoginDialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
			{
				RecordQuery^ theRecordQuery = gcnew RecordQuery(theLoginDialog->LeaguerSuite0);
				this->Hide();
				if(theRecordQuery->ShowDialog(this) == System::Windows::Forms::DialogResult::Cancel)
				{
					delete theRecordQuery;
					this->Show();
				}
			}
			delete theLoginDialog;
		}
	private: 
		System::Void pictureBox7_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			// form register.
			Register^ theRegister = gcnew Register();
			if( theRegister->ShowDialog(this) == System::Windows::Forms::DialogResult::OK )
			{
				this->Hide();
				会员注册^ theRegisterPage = gcnew 会员注册(false);
				if( theRegisterPage->ShowDialog(this) == System::Windows::Forms::DialogResult::OK )
				{
					System::Media::SystemSounds::Asterisk->Play();
					MessageBox::Show("注册成功.");					
				}
				this->Show();
				delete theRegisterPage;
			}
			else
			{
				this->Hide();
				会员注册^ theRegisterPage = gcnew 会员注册(true);
				if( theRegisterPage->ShowDialog(this) == System::Windows::Forms::DialogResult::OK )
				{
					System::Media::SystemSounds::Asterisk->Play();
					MessageBox::Show("注册成功.");					
				}
				this->Show();
				delete theRegisterPage;
			}
			delete theRegister;
		}
	private: 
		System::Void pictureBox8_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			this->Close();
		}
	private: 
		System::Void pictureBox9_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			DebugTools^ theDebugTools = gcnew DebugTools();
			System::Windows::Forms::DialogResult dr = theDebugTools->ShowDialog(this);
			if( dr == System::Windows::Forms::DialogResult::OK )
			{ // 10 new leaguers.
				SqlClient::SqlConnection^ conn = gcnew SqlConnection( "Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;" );
				conn->Open();
				SqlClient::SqlCommand^ cmd = conn->CreateCommand();
				cmd->CommandType = CommandType::Text;
				for( int i=0; i<10; i++ )
				{
					String^ userIDString = "\'" + Randoms::GetRandoms::GetOneDigit() + Randoms::GetRandoms::GetOneDigit()
						+ Randoms::GetRandoms::GetOneAlphabet() + Randoms::GetRandoms::GetOneAlphabet()
						+ Randoms::GetRandoms::GetOneAlphabet() + Randoms::GetRandoms::GetOneAlphabet()
						+ Randoms::GetRandoms::GetOneAlphabet() + Randoms::GetRandoms::GetOneAlphabet() + "\'";
					String^ fullNameString = "\'" + Randoms::GetRandoms::GetOneChineseCharacter()
													+ Randoms::GetRandoms::GetOneChineseCharacter()
													+ Randoms::GetRandoms::GetOneChineseCharacter() + "\'";
					String^ passwordString = "\'" + Randoms::GetRandoms::GetOneDigit() + Randoms::GetRandoms::GetOneAlphabet()
						+ Randoms::GetRandoms::GetOneDigit() + Randoms::GetRandoms::GetOneAlphabet() + "\'";
					String^ certificateString = 
						"\'" + Randoms::GetRandoms::GetOneAlphabet() + Randoms::GetRandoms::GetOneAlphabet()
						+ Randoms::GetRandoms::GetOneAlphabet() + Randoms::GetRandoms::GetOneAlphabet()
						+ Randoms::GetRandoms::GetOneDigit() + Randoms::GetRandoms::GetOneDigit() + "\'";
					String^ accumulatePointsString = Randoms::GetRandoms::GetOneInteger(300, 100000).ToString();
					array<String^>^ typeArray = gcnew array<String^>(4) { "\'Nor\'", "\'VIP\'", "\'Stu\'", "\'ViM\'" };
					String^ typeString = typeArray[Randoms::GetRandoms::GetOneInteger(0, 4)];
					String^ schoolString;
					if( typeString == "\'Stu\'" || typeString == "\'ViM\'" )
					{
						schoolString = "\'" + Randoms::GetRandoms::GetOneChineseCharacter()
													+ Randoms::GetRandoms::GetOneChineseCharacter()
													+ Randoms::GetRandoms::GetOneChineseCharacter() 
													+ Randoms::GetRandoms::GetOneDigit() + Randoms::GetRandoms::GetOneAlphabet()
													+ Randoms::GetRandoms::GetOneChineseCharacter() + "\'";
					}
					else
					{
						schoolString = "NULL";
					}
					cmd->CommandText = "INSERT INTO dbo.Leaguer VALUES(" + userIDString + "," +  fullNameString + ","
												+ passwordString + "," + certificateString + "," + accumulatePointsString + "," 
												+ typeString + "," + schoolString + ")";
					cmd->ExecuteNonQuery();
				}
				conn->Close();
				System::Media::SystemSounds::Asterisk->Play();
				MessageBox::Show("添加成功.");
			}
			else if( dr == System::Windows::Forms::DialogResult::Yes )
			{ // 50 new commodities.
				SqlClient::SqlConnection^ conn = gcnew SqlConnection( "Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;" );
				conn->Open();
				SqlClient::SqlCommand^ cmd = conn->CreateCommand();
				cmd->CommandType = CommandType::Text;
				SqlClient::SqlDataAdapter^ extrasAdapter = gcnew SqlClient::SqlDataAdapter( "SELECT * FROM dbo.Extras", gcnew SqlConnection("Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;") );
				DataTable^ extrasTable = gcnew DataTable();
				extrasAdapter->Fill(extrasTable);
				int initID = Convert::ToUInt32(extrasTable->Rows[0]["Extras"]);
				for( int i=0; i<50; i++ )
				{
					String^ commodityIDString = (i + initID).ToString();
					String^ priceString = Randoms::GetRandoms::GetOneInteger(100, 50001).ToString();
					int discount = Randoms::GetRandoms::GetOneInteger(7, 11);
					String^ accumulateMultipleString = Randoms::GetRandoms::GetOneInteger(1, 4).ToString();
					int presentRehovedNumber = Randoms::GetRandoms::GetOneInteger(0, 3);
					int presentBaseNumber;
					if( presentRehovedNumber == 0 )
					{
						presentBaseNumber = 0;
					}
					else
					{
						presentBaseNumber = presentRehovedNumber + Randoms::GetRandoms::GetOneInteger(0, 4);
					}
					if( presentBaseNumber == 4 && presentRehovedNumber == 2)
					{
						presentBaseNumber = 2;
						presentRehovedNumber = 1;
					}
					if( presentBaseNumber == 2 && presentRehovedNumber == 2 )
					{
						presentBaseNumber = 1;
						presentRehovedNumber = 1;
					}
					String^ nameString = "\'" + Randoms::GetRandoms::GetOneChineseCharacter() 
						+ Randoms::GetRandoms::GetOneChineseCharacter() + Randoms::GetRandoms::GetOneChineseCharacter()
						+ Randoms::GetRandoms::GetOneChineseCharacter() + "\'";
					String^ typeString;
					if( discount == 10 )
					{
						if( presentBaseNumber == 0 )
						{ // no presents.
							switch(Randoms::GetRandoms::GetOneInteger(0, 3))
							{
							case 0: typeString = "\'NNN\'"; break;
							case 1: typeString = "\'NNL\'"; break;
							case 2: typeString = "\'NNR\'"; break;
							}
						}
						else
						{ // presents included.
							switch(Randoms::GetRandoms::GetOneInteger(0, 3))
							{
							case 0: typeString = "\'PN0\'"; break;
							case 1: typeString = "\'PL0\'"; break;
							case 2: typeString = "\'PR0\'"; break;
							}
						}
					}
					else
					{
						switch(Randoms::GetRandoms::GetOneInteger(0, 3))
						{
						case 0: typeString = "\'DNN\'"; break;
						case 1: typeString = "\'DNR\'"; break;
						case 2: typeString = "\'DNL\'"; break;
						}
					}
					cmd->CommandText = "INSERT INTO dbo.CommodityInfo VALUES(" + commodityIDString + "," + priceString
												+ "," + discount.ToString() + "," + accumulateMultipleString + ","
												+ presentRehovedNumber.ToString() + "," + presentBaseNumber.ToString() + ","
												+ nameString + "," + typeString + ")";
					cmd->ExecuteNonQuery();
					cmd->CommandText = "INSERT INTO dbo.Stock VALUES(" + commodityIDString + ","
												+ Randoms::GetRandoms::GetOneInteger(20, 501).ToString() + ")";
					cmd->ExecuteNonQuery();
				}
				conn->Close();
				extrasTable->Rows[0]["Extras"] = initID + 50;
				SqlClient::SqlCommandBuilder^ builder = gcnew SqlClient::SqlCommandBuilder(extrasAdapter);
				extrasAdapter->Update(extrasTable);
				delete builder;
				System::Media::SystemSounds::Asterisk->Play();
				MessageBox::Show("添加成功.");
			}
			delete theDebugTools;
		}
	};
}


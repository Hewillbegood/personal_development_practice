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
	/// PayPage 摘要
	/// </summary>
	public ref class PayPage : public System::Windows::Forms::Form
	{
	public:
		PayPage(LCP::LeaguerSuite^ inLeaguerSuite, ArrayList^ inArrayList)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
			this->ShoppingListSended = inArrayList;
			this->LeaguerSuite0 = inLeaguerSuite;
			String^ leaguerSortStr;
			switch(this->LeaguerSuite0->leaguer->Sort)
			{
			case LCP::LeaguerType::Nope: leaguerSortStr = ""; break;
			case LCP::LeaguerType::Normal: leaguerSortStr = L"会员"; break;
			case LCP::LeaguerType::VIP: leaguerSortStr = L"VIP 会员"; break;
			case LCP::LeaguerType::Student: leaguerSortStr = L"学生会员"; break;
			case LCP::LeaguerType::ViM_Student: leaguerSortStr = L"VIP 学生会员"; break;
			}
			if(this->LeaguerSuite0->leaguer->Sort != LCP::LeaguerType::Nope)
			{
				this->label4->Text = "." + "欢迎您, " + leaguerSortStr + " " + this->LeaguerSuite0->leaguer->FullName->Trim()
										+ L", 您的积分是 " +  Convert::ToDouble(this->LeaguerSuite0->leaguer->AccumulatePoints) / 100;
			}
			else
			{
				this->label4->Text = "." + "欢迎您, " + leaguerSortStr + " " + this->LeaguerSuite0->leaguer->FullName;
			}
			// hints: bool CannotBuy, credit poundages, sort and resort the ShoppingListSended, init and reinit kinds of variables.
			//
			LCP::PaymentMode::CannotBuy = false;
			LCP::PaymentMode::RealtimeSubmittedDealAmount = 0;	// unit name: fen.
			LCP::PaymentMode::RealtimeNeedFillingCreditAmount = 0;
			LCP::PaymentMode::RealtimeNeedFillingCashAmount = 0;
			LCP::PaymentMode::RealtimeNeedFillingVoncherAmount = 0;
			LCP::PaymentMode::RealtimeNeedFillingAccPointsAmount = 0;
			LCP::PaymentMode::CreditPoundage = 0;
			//
			// boring.
			//
			if( this->LeaguerSuite0->leaguer->Sort == LCP::LeaguerType::Nope )
			{
				this->tmd4->Enabled = false;
				this->button4->Enabled = false;
			}
			// rehovedAmountLabel, realtimeNeedFillingAmountLabel, creditPoundageLabel.
			//
			String^ rehovedDealAmountStr = (Convert::ToDouble(LCP::PaymentMode::RehovedDealAmount) / 100).ToString("F2");
			this->rehovedAmountLabel->Text = L"您所购买的所有商品的总价格 /￥: " + rehovedDealAmountStr + ".";
			String^ realtimeNeedFillingAmountStr = 
				(Convert::ToDouble(LCP::PaymentMode::RehovedDealAmount - LCP::PaymentMode::RealtimeSubmittedDealAmount)
				/ 100).ToString("F2");
			this->realtimeNeedFillingAmountLabel->Text = L"目前的付款方案尚未覆盖的部分 /￥: " + realtimeNeedFillingAmountStr 
				+".";
			this->creditPoundageLabel->Text = L"信用卡支付所需手续费 /￥: 0.";
			//
			// sort ShoppingListSended.
			//
			switch(this->LeaguerSuite0->leaguer->Sort)
			{
			case LCP::LeaguerType::Nope: {
				LCP::ComparerForNope^ tmpComparer = gcnew LCP::ComparerForNope();
				this->ShoppingListSended->Sort(tmpComparer);
				break;
				}
			case LCP::LeaguerType::Normal: {
				LCP::ComparerForNormal^ tmpComparer = gcnew LCP::ComparerForNormal();
				this->ShoppingListSended->Sort(tmpComparer);
				break;
				}
			case LCP::LeaguerType::VIP: {
				LCP::ComparerForVIP^ tmpComparer = gcnew LCP::ComparerForVIP();
				this->ShoppingListSended->Sort(tmpComparer);
				break;
				}
			case LCP::LeaguerType::Student: {
				LCP::ComparerForStudent^ tmpComparer = gcnew LCP::ComparerForStudent();
				this->ShoppingListSended->Sort(tmpComparer);
				break;
				}
			case LCP::LeaguerType::ViM_Student: {
				LCP::ComparerForViM_Student^ tmpComparer = gcnew LCP::ComparerForViM_Student();
				this->ShoppingListSended->Sort(tmpComparer);
				break;
				}
			}
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~PayPage()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::GroupBox^  groupBox1;

	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  tmd2;
	private: System::Windows::Forms::TextBox^  tmd3;
	private: System::Windows::Forms::TextBox^  tmd4;


	private: System::Windows::Forms::TextBox^  tmd1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  realtimeNeedFillingAmountLabel;

	private: System::Windows::Forms::Label^  rehovedAmountLabel;


	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  creditPoundageLabel;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Label^  tipForFullLabel;
	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(PayPage::typeid));
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tipForFullLabel = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->creditPoundageLabel = (gcnew System::Windows::Forms::Label());
			this->realtimeNeedFillingAmountLabel = (gcnew System::Windows::Forms::Label());
			this->rehovedAmountLabel = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tmd2 = (gcnew System::Windows::Forms::TextBox());
			this->tmd3 = (gcnew System::Windows::Forms::TextBox());
			this->tmd4 = (gcnew System::Windows::Forms::TextBox());
			this->tmd1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Location = System::Drawing::Point(83, 9);
			this->label4->Name = L"label4";
			this->label4->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label4->Size = System::Drawing::Size(417, 31);
			this->label4->TabIndex = 0;
			this->label4->Text = L"label4";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::Transparent;
			this->groupBox1->Controls->Add(this->tipForFullLabel);
			this->groupBox1->Controls->Add(this->button5);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->creditPoundageLabel);
			this->groupBox1->Controls->Add(this->realtimeNeedFillingAmountLabel);
			this->groupBox1->Controls->Add(this->rehovedAmountLabel);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->button6);
			this->groupBox1->Controls->Add(this->button4);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->tmd2);
			this->groupBox1->Controls->Add(this->tmd3);
			this->groupBox1->Controls->Add(this->tmd4);
			this->groupBox1->Controls->Add(this->tmd1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->ForeColor = System::Drawing::Color::White;
			this->groupBox1->Location = System::Drawing::Point(59, 41);
			this->groupBox1->Margin = System::Windows::Forms::Padding(50);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(10);
			this->groupBox1->Size = System::Drawing::Size(391, 489);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"输入每种付款方式的付款数额.";
			// 
			// tipForFullLabel
			// 
			this->tipForFullLabel->Location = System::Drawing::Point(13, 379);
			this->tipForFullLabel->Name = L"tipForFullLabel";
			this->tipForFullLabel->Size = System::Drawing::Size(365, 24);
			this->tipForFullLabel->TabIndex = 23;
			this->tipForFullLabel->Text = L"当前付款方案未能覆盖商品总价格, 不能完成支付.";
			// 
			// button5
			// 
			this->button5->Enabled = false;
			this->button5->ForeColor = System::Drawing::Color::Black;
			this->button5->Location = System::Drawing::Point(210, 436);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(168, 40);
			this->button5->TabIndex = 22;
			this->button5->Text = L"确认并完成支付";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &PayPage::button5_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(13, 72);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(317, 42);
			this->label8->TabIndex = 21;
			this->label8->Text = L"对于非会员和普通会员:\r\n信用卡支付不满 30 元时需要付 3 元手续费.";
			// 
			// creditPoundageLabel
			// 
			this->creditPoundageLabel->AutoSize = true;
			this->creditPoundageLabel->ForeColor = System::Drawing::Color::White;
			this->creditPoundageLabel->Location = System::Drawing::Point(130, 209);
			this->creditPoundageLabel->Name = L"creditPoundageLabel";
			this->creditPoundageLabel->Size = System::Drawing::Size(55, 21);
			this->creditPoundageLabel->TabIndex = 20;
			this->creditPoundageLabel->Text = L"label8";
			// 
			// realtimeNeedFillingAmountLabel
			// 
			this->realtimeNeedFillingAmountLabel->AutoSize = true;
			this->realtimeNeedFillingAmountLabel->Location = System::Drawing::Point(13, 354);
			this->realtimeNeedFillingAmountLabel->Name = L"realtimeNeedFillingAmountLabel";
			this->realtimeNeedFillingAmountLabel->Size = System::Drawing::Size(55, 21);
			this->realtimeNeedFillingAmountLabel->TabIndex = 18;
			this->realtimeNeedFillingAmountLabel->Text = L"label3";
			// 
			// rehovedAmountLabel
			// 
			this->rehovedAmountLabel->AutoSize = true;
			this->rehovedAmountLabel->Location = System::Drawing::Point(13, 329);
			this->rehovedAmountLabel->Name = L"rehovedAmountLabel";
			this->rehovedAmountLabel->Size = System::Drawing::Size(55, 21);
			this->rehovedAmountLabel->TabIndex = 17;
			this->rehovedAmountLabel->Text = L"label3";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(13, 171);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(95, 21);
			this->label7->TabIndex = 16;
			this->label7->Text = L"信用卡 / ￥:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(13, 240);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(95, 21);
			this->label6->TabIndex = 15;
			this->label6->Text = L"代金券 / 张:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(13, 287);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(95, 21);
			this->label5->TabIndex = 14;
			this->label5->Text = L"积　分 / 点:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 124);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(95, 21);
			this->label2->TabIndex = 12;
			this->label2->Text = L"现　金 / ￥:";
			// 
			// button6
			// 
			this->button6->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button6->ForeColor = System::Drawing::Color::Black;
			this->button6->Location = System::Drawing::Point(17, 436);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(168, 40);
			this->button6->TabIndex = 11;
			this->button6->Text = L"返回编辑购物列表";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->ForeColor = System::Drawing::Color::Black;
			this->button4->Location = System::Drawing::Point(262, 286);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(116, 29);
			this->button4->TabIndex = 9;
			this->button4->Text = L"提交";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &PayPage::button4_Click);
			// 
			// button3
			// 
			this->button3->ForeColor = System::Drawing::Color::Black;
			this->button3->Location = System::Drawing::Point(262, 240);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(116, 29);
			this->button3->TabIndex = 8;
			this->button3->Text = L"提交";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &PayPage::button3_Click);
			// 
			// button2
			// 
			this->button2->ForeColor = System::Drawing::Color::Black;
			this->button2->Location = System::Drawing::Point(262, 171);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(116, 29);
			this->button2->TabIndex = 7;
			this->button2->Text = L"提交";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &PayPage::button2_Click);
			// 
			// button1
			// 
			this->button1->ForeColor = System::Drawing::Color::Black;
			this->button1->Location = System::Drawing::Point(262, 124);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(116, 29);
			this->button1->TabIndex = 6;
			this->button1->Text = L"提交";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &PayPage::button1_Click);
			// 
			// tmd2
			// 
			this->tmd2->Location = System::Drawing::Point(134, 171);
			this->tmd2->Margin = System::Windows::Forms::Padding(9);
			this->tmd2->Name = L"tmd2";
			this->tmd2->Size = System::Drawing::Size(116, 29);
			this->tmd2->TabIndex = 5;
			this->tmd2->Text = L"0";
			this->tmd2->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tmd3
			// 
			this->tmd3->Location = System::Drawing::Point(134, 240);
			this->tmd3->Margin = System::Windows::Forms::Padding(9);
			this->tmd3->Name = L"tmd3";
			this->tmd3->Size = System::Drawing::Size(116, 29);
			this->tmd3->TabIndex = 4;
			this->tmd3->Text = L"0";
			this->tmd3->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tmd4
			// 
			this->tmd4->Location = System::Drawing::Point(134, 287);
			this->tmd4->Margin = System::Windows::Forms::Padding(9);
			this->tmd4->Name = L"tmd4";
			this->tmd4->Size = System::Drawing::Size(116, 29);
			this->tmd4->TabIndex = 3;
			this->tmd4->Text = L"0";
			this->tmd4->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// tmd1
			// 
			this->tmd1->Location = System::Drawing::Point(134, 124);
			this->tmd1->Margin = System::Windows::Forms::Padding(9);
			this->tmd1->Name = L"tmd1";
			this->tmd1->Size = System::Drawing::Size(116, 29);
			this->tmd1->TabIndex = 1;
			this->tmd1->Text = L"0";
			this->tmd1->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(359, 42);
			this->label1->TabIndex = 0;
			this->label1->Text = L"懒于写验证代码了, 码农干的苦力不是一般的无聊.\r\n如果胡乱输入, 程序异常了, 不是我的毛病.";
			// 
			// PayPage
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 21);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(512, 589);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label4);
			this->Font = (gcnew System::Drawing::Font(L"微软雅黑", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->ForeColor = System::Drawing::Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(5);
			this->MaximizeBox = false;
			this->Name = L"PayPage";
			this->Opacity = 0.98;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"支付";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	public: property LCP::LeaguerSuite^ LeaguerSuite0;
	public: property ArrayList^ ShoppingListSended;
	private: 
		System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			int a = Convert::ToUInt32(Convert::ToDouble(tmd1->Text) * 100);
			LCP::PaymentMode::RealtimeNeedFillingCashAmount = a;
			LCP::PaymentMode::RealtimeSubmittedDealAmount = LCP::PaymentMode::RealtimeNeedFillingCashAmount
																		+ LCP::PaymentMode::RealtimeNeedFillingCreditAmount
																		+ LCP::PaymentMode::RealtimeNeedFillingVoncherAmount
																		+ LCP::PaymentMode::RealtimeNeedFillingAccPointsAmount;
			int b = LCP::PaymentMode::RehovedDealAmount - LCP::PaymentMode::RealtimeSubmittedDealAmount;
			String^ realtimeNeedFillingAmountStr = (Convert::ToDouble(b) / 100).ToString("F2");
			this->realtimeNeedFillingAmountLabel->Text = L"目前的付款方案尚未覆盖的部分 /￥: " + realtimeNeedFillingAmountStr 
				+".";
			if( b <= 0 )
			{
				this->tipForFullLabel->Text = L"付款方案已能覆盖商品总价格, 可以完成支付.";
				this->button5->Enabled = true;
			}
			else
			{
				this->tipForFullLabel->Text = L"当前付款方案未能覆盖商品总价格, 不能完成支付.";
				this->button5->Enabled = false;
			}
		}
	private: 
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			int a = Convert::ToUInt32(Convert::ToDouble(tmd2->Text) * 100);
			LCP::PaymentMode::RealtimeNeedFillingCreditAmount = a;
			LCP::PaymentMode::RealtimeSubmittedDealAmount = LCP::PaymentMode::RealtimeNeedFillingCashAmount
																		+ LCP::PaymentMode::RealtimeNeedFillingCreditAmount
																		+ LCP::PaymentMode::RealtimeNeedFillingVoncherAmount
																		+ LCP::PaymentMode::RealtimeNeedFillingAccPointsAmount;
			int b = LCP::PaymentMode::RehovedDealAmount - LCP::PaymentMode::RealtimeSubmittedDealAmount;
			String^ realtimeNeedFillingAmountStr = (Convert::ToDouble(b) / 100).ToString("F2");
			this->realtimeNeedFillingAmountLabel->Text = L"目前的付款方案尚未覆盖的部分 /￥: " + realtimeNeedFillingAmountStr 
				+".";
			if( b <= 0 )
			{
				this->tipForFullLabel->Text = L"付款方案已能覆盖商品总价格, 可以完成支付.";
				this->button5->Enabled = true;
			}
			else
			{
				this->tipForFullLabel->Text = L"当前付款方案未能覆盖商品总价格, 不能完成支付.";
				this->button5->Enabled = false;
			}
			// creditPoundageLabel.
			//
			if( (this->LeaguerSuite0->leaguer->Sort == LCP::LeaguerType::Nope
				|| this->LeaguerSuite0->leaguer->Sort == LCP::LeaguerType::Normal) && a < 3000 && a > 0)
			{
				LCP::PaymentMode::CreditPoundage = 300;	// unit name: fen.
				this->creditPoundageLabel->Text = L"信用卡支付所需手续费 /￥: 3.00.";
			}
			else
			{
				LCP::PaymentMode::CreditPoundage = 0;	// unit name: fen.
				this->creditPoundageLabel->Text = L"信用卡支付所需手续费 /￥: 0.";
			}
		}
	private: 
		System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
		{ // tmd3.
			int a = Convert::ToUInt32(tmd3->Text) * 10000;
			LCP::PaymentMode::RealtimeNeedFillingVoncherAmount = a;
			LCP::PaymentMode::RealtimeSubmittedDealAmount = LCP::PaymentMode::RealtimeNeedFillingCashAmount
																		+ LCP::PaymentMode::RealtimeNeedFillingCreditAmount
																		+ LCP::PaymentMode::RealtimeNeedFillingVoncherAmount
																		+ LCP::PaymentMode::RealtimeNeedFillingAccPointsAmount;
			int b = LCP::PaymentMode::RehovedDealAmount - LCP::PaymentMode::RealtimeSubmittedDealAmount;
			String^ realtimeNeedFillingAmountStr = (Convert::ToDouble(b) / 100).ToString("F2");
			this->realtimeNeedFillingAmountLabel->Text = L"目前的付款方案尚未覆盖的部分 /￥: " + realtimeNeedFillingAmountStr 
				+".";
			if( b <= 0 )
			{
				this->tipForFullLabel->Text = L"付款方案已能覆盖商品总价格, 可以完成支付.";
				this->button5->Enabled = true;
			}
			else
			{
				this->tipForFullLabel->Text = L"当前付款方案未能覆盖商品总价格, 不能完成支付.";
				this->button5->Enabled = false;
			}
		}
	private: 
		System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			int a = Convert::ToUInt32(Convert::ToDouble(tmd4->Text) * 100);
			if( a <= this->LeaguerSuite0->leaguer->AccumulatePoints )
			{
				LCP::PaymentMode::RealtimeNeedFillingAccPointsAmount = a;
				LCP::PaymentMode::RealtimeSubmittedDealAmount = LCP::PaymentMode::RealtimeNeedFillingCashAmount
																			+ LCP::PaymentMode::RealtimeNeedFillingCreditAmount
																			+ LCP::PaymentMode::RealtimeNeedFillingVoncherAmount
																			+ LCP::PaymentMode::RealtimeNeedFillingAccPointsAmount;
				int b = LCP::PaymentMode::RehovedDealAmount - LCP::PaymentMode::RealtimeSubmittedDealAmount;
				String^ realtimeNeedFillingAmountStr = (Convert::ToDouble(b) / 100).ToString("F2");
				this->realtimeNeedFillingAmountLabel->Text = L"目前的付款方案尚未覆盖的部分 /￥: "
																	+ realtimeNeedFillingAmountStr + ".";
				if( b <= 0 )
				{
					this->tipForFullLabel->Text = L"付款方案已能覆盖商品总价格, 可以完成支付.";
					this->button5->Enabled = true;
				}
				else
				{
					this->tipForFullLabel->Text = L"当前付款方案未能覆盖商品总价格, 不能完成支付.";
					this->button5->Enabled = false;
				}
			}
			else
			{
				System::Media::SystemSounds::Exclamation->Play();
				MessageBox::Show("您的积分不足.");
			}
		}
	private: 
		System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			int CreditAmountBackup = LCP::PaymentMode::RealtimeNeedFillingCreditAmount;			// unit name: fen.
			int CashAmountBackup = LCP::PaymentMode::RealtimeNeedFillingCashAmount;				// unit name: fen.
			int VoncherAmountBackup = LCP::PaymentMode::RealtimeNeedFillingVoncherAmount;		// unit name: fen.
			int AccPointsAmountBackup = LCP::PaymentMode::RealtimeNeedFillingAccPointsAmount;	// unit name: fen.
			for each(LCP::DealSuite^ iteratorDealSuite in this->ShoppingListSended)
			{
				iteratorDealSuite->paymentMode->ErasePaymentFills();
				// void FillPayments(LeaguerType inLeaguerSort, Commodity^ inCommodity)
				//
				iteratorDealSuite->paymentMode->FillPayments( this->LeaguerSuite0->leaguer->Sort, 
																		iteratorDealSuite->commodity );
			}
			if( LCP::PaymentMode::CannotBuy == false )
			{
				SqlConnection^ conn = gcnew SqlConnection("Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;");
				conn->Open();
				SqlCommand^ theCmd = conn->CreateCommand();
				theCmd->CommandType = CommandType::Text;
				for each(LCP::DealSuite^ iteratorDealSuite in this->ShoppingListSended)
				{
					// virtual void UpdateAccumulatePoints(Commodity^ inCommodity, PaymentMode^ inPaymentMode)
					//
					this->LeaguerSuite0->leaguer->UpdateAccumulatePoints( iteratorDealSuite->commodity, 
																					iteratorDealSuite->paymentMode );
					iteratorDealSuite->paymentMode->Stock -= iteratorDealSuite->paymentMode->PresentQuantity
																		+ iteratorDealSuite->paymentMode->CommodityQuantity;
					iteratorDealSuite->stockDS->Tables["Stock"]->Rows[0]["Stock"] = iteratorDealSuite->paymentMode->Stock;
					//
					// search MSDN to find SqlDataAdapter::Update(...)'s requirements.
					//
					SqlCommandBuilder^ theSCB = gcnew SqlCommandBuilder(iteratorDealSuite->stockDA);
					iteratorDealSuite->stockDA->Update(iteratorDealSuite->stockDS, "Stock");
					delete theSCB;
					//
					// INSERT to dbo.SalesLog.
					//
					theCmd->CommandText = "INSERT INTO dbo.SalesLog VALUES(\'" 
						+ this->LeaguerSuite0->leaguer->UserID + "\', \'" 
						+ iteratorDealSuite->commodity->CommodityID.ToString() + "\', \'" 
						+ iteratorDealSuite->commodity->CommodityName + "\', \'" 
						+ iteratorDealSuite->paymentMode->CommodityQuantity.ToString() + "\', \'"
						+ iteratorDealSuite->paymentMode->PresentQuantity.ToString() + "\', \'"
						+ DateTime::Now.ToString() + "\')";
					theCmd->ExecuteNonQuery();
				}
				conn->Close();
				this->LeaguerSuite0->leaguer->OddChangeUAP();
				//
				// database update.
				//
				this->LeaguerSuite0->leaguerDS->Tables["Leaguer"]->Rows[0]["AccumulatePoints"] = 
					this->LeaguerSuite0->leaguer->AccumulatePoints;
				SqlCommandBuilder^ thisSCB = gcnew SqlCommandBuilder(this->LeaguerSuite0->leaguerDA);
				this->LeaguerSuite0->leaguerDA->Update(this->LeaguerSuite0->leaguerDS, "Leaguer");
				delete thisSCB;
				//
				// then update sales log.
				// succuss messagebox.
				// a big bug.
				//
				String^ newAccumulatePointsStr;
				if( this->LeaguerSuite0->leaguer->Sort == LCP::LeaguerType::Nope )
				{
					newAccumulatePointsStr = "";
				}
				else
				{
					newAccumulatePointsStr = ".\n本次交易后您的积分为: " 
													+ Convert::ToDouble(this->LeaguerSuite0->leaguer->AccumulatePoints) / 100;
				}
				MessageBox::Show(L"本次交易的商品总价格 /￥: " + Convert::ToDouble(LCP::PaymentMode::RehovedDealAmount) / 100
					+ ".\n实付金额 /￥: " + 
					Convert::ToDouble(CreditAmountBackup - LCP::PaymentMode::RealtimeNeedFillingCreditAmount
					+ CashAmountBackup - LCP::PaymentMode::RealtimeNeedFillingCashAmount
					+ LCP::PaymentMode::CreditPoundage) / 100
					+ ".\n现金找零 /￥: " 
					+ Convert::ToDouble(LCP::PaymentMode::RealtimeNeedFillingCashAmount) / 100
					+ newAccumulatePointsStr + ".", 
					"交易成功", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
				this->DialogResult = System::Windows::Forms::DialogResult::OK;
			}
			else
			{
				LCP::PaymentMode::CannotBuy = false;
				LCP::PaymentMode::RealtimeNeedFillingCreditAmount = CreditAmountBackup;			// unit name: fen.
				LCP::PaymentMode::RealtimeNeedFillingCashAmount = CashAmountBackup;				// unit name: fen.
				LCP::PaymentMode::RealtimeNeedFillingVoncherAmount = VoncherAmountBackup;		// unit name: fen.
				LCP::PaymentMode::RealtimeNeedFillingAccPointsAmount = AccPointsAmountBackup;	// unit name: fen.
				System::Media::SystemSounds::Exclamation->Play();
				MessageBox::Show("根据您的用户类型, 奢侈类商品不能使用代金券购买, 请检查您的付款方案.");
			}
		}
	};
}

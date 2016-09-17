#pragma once



namespace ATM_GH2005 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// CommodityEntering 摘要
	/// </summary>
	public ref class CommodityEntering : public System::Windows::Forms::Form
	{
	public:
		CommodityEntering(LCP::LeaguerSuite^ inLeaguerSuite)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
			this->ShoppingList = gcnew ArrayList();
			//
			// fill listView2 with all commodities' info WHERE the stack > 0.
			//
			SqlClient::SqlDataAdapter^ adapterForListV2 = gcnew SqlClient::SqlDataAdapter( "SELECT dc.CommodityID, dc.Name FROM dbo.CommodityInfo AS dc INNER JOIN dbo.Stock AS ds ON dc.CommodityID=ds.CommodityID WHERE ds.Stock<>0", gcnew SqlConnection("Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;") );
			//
			// test that problem. and begin at filling listView2.
			//
			DataTable^ dataTbForListV2 = gcnew DataTable();
			adapterForListV2->Fill(dataTbForListV2);
			for( int i = 0; i < dataTbForListV2->Rows->Count; i++ )
			{
				ListViewItem^ tmpLVI = gcnew ListViewItem( gcnew cli::array<System::String^>(2) {dataTbForListV2->Rows[i]["CommodityID"]->ToString(), dataTbForListV2->Rows[i]["Name"]->ToString()}, -1 );
				this->listView2->Items->AddRange( gcnew cli::array<ListViewItem^>(1) {tmpLVI} );
			}
			this->listView2->MultiSelect = false;
			//
			// using label4 to display leaguer info.
			//
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
			// statics initializations.
			LCP::PaymentMode::RehovedDealAmount = 0;
			this->label5->Text = L"当前总交易额 / ￥: " + LCP::PaymentMode::RehovedDealAmount + ".00";
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~CommodityEntering()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^  listView1;
	protected: 
	private: System::Windows::Forms::ColumnHeader^  CommodityID;
	private: System::Windows::Forms::ColumnHeader^  Name0;
	private: System::Windows::Forms::ColumnHeader^  Price;
	private: System::Windows::Forms::ColumnHeader^  Discount;
	private: System::Windows::Forms::ColumnHeader^  AmountToBuy;
	private: System::Windows::Forms::ColumnHeader^  RehovedPayAmount;
	private: System::Windows::Forms::ColumnHeader^  PresentStrategy;
	private: System::Windows::Forms::ColumnHeader^  PresentAmount;
	private: System::Windows::Forms::ColumnHeader^  CommodityType;
	private: System::Windows::Forms::ListView^  listView2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::ColumnHeader^  CommodityID1;
	private: System::Windows::Forms::ColumnHeader^  Name1;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CommodityEntering::typeid));
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->CommodityID = (gcnew System::Windows::Forms::ColumnHeader());
			this->Name0 = (gcnew System::Windows::Forms::ColumnHeader());
			this->Price = (gcnew System::Windows::Forms::ColumnHeader());
			this->Discount = (gcnew System::Windows::Forms::ColumnHeader());
			this->AmountToBuy = (gcnew System::Windows::Forms::ColumnHeader());
			this->RehovedPayAmount = (gcnew System::Windows::Forms::ColumnHeader());
			this->PresentStrategy = (gcnew System::Windows::Forms::ColumnHeader());
			this->PresentAmount = (gcnew System::Windows::Forms::ColumnHeader());
			this->CommodityType = (gcnew System::Windows::Forms::ColumnHeader());
			this->listView2 = (gcnew System::Windows::Forms::ListView());
			this->CommodityID1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->Name1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// listView1
			// 
			this->listView1->CausesValidation = false;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(9) {this->CommodityID, this->Name0, 
				this->Price, this->Discount, this->AmountToBuy, this->RehovedPayAmount, this->PresentStrategy, this->PresentAmount, this->CommodityType});
			this->listView1->Font = (gcnew System::Drawing::Font(L"微软雅黑", 10));
			this->listView1->FullRowSelect = true;
			this->listView1->GridLines = true;
			this->listView1->Location = System::Drawing::Point(51, 317);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(830, 260);
			this->listView1->TabIndex = 0;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// CommodityID
			// 
			this->CommodityID->Text = L"商品 ID";
			this->CommodityID->Width = 81;
			// 
			// Name0
			// 
			this->Name0->Text = L"商品名称";
			this->Name0->Width = 170;
			// 
			// Price
			// 
			this->Price->Text = L"单价 /￥";
			this->Price->Width = 77;
			// 
			// Discount
			// 
			this->Discount->Text = L"折扣";
			this->Discount->Width = 46;
			// 
			// AmountToBuy
			// 
			this->AmountToBuy->Text = L"欲购数量";
			this->AmountToBuy->Width = 67;
			// 
			// RehovedPayAmount
			// 
			this->RehovedPayAmount->Text = L"应付款额 /￥";
			this->RehovedPayAmount->Width = 92;
			// 
			// PresentStrategy
			// 
			this->PresentStrategy->Text = L"赠品说明";
			this->PresentStrategy->Width = 66;
			// 
			// PresentAmount
			// 
			this->PresentAmount->Text = L"赠品数量";
			this->PresentAmount->Width = 65;
			// 
			// CommodityType
			// 
			this->CommodityType->Text = L"商品类型";
			this->CommodityType->Width = 75;
			// 
			// listView2
			// 
			this->listView2->CausesValidation = false;
			this->listView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->CommodityID1, this->Name1});
			this->listView2->Font = (gcnew System::Drawing::Font(L"微软雅黑", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->listView2->FullRowSelect = true;
			this->listView2->GridLines = true;
			this->listView2->Location = System::Drawing::Point(12, 12);
			this->listView2->Name = L"listView2";
			this->listView2->Size = System::Drawing::Size(239, 299);
			this->listView2->TabIndex = 1;
			this->listView2->UseCompatibleStateImageBehavior = false;
			this->listView2->View = System::Windows::Forms::View::Details;
			// 
			// CommodityID1
			// 
			this->CommodityID1->Text = L"商品 ID";
			this->CommodityID1->Width = 71;
			// 
			// Name1
			// 
			this->Name1->Text = L"商品名称";
			this->Name1->Width = 138;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->CausesValidation = false;
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(257, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(174, 152);
			this->label1->TabIndex = 2;
			this->label1->Text = L"在左侧的列表试图内选择您要添加的商品, 并在下方文本框中填写要购买的数量, 完成后单击\"添加\"按钮以添加购买项. 库存为 0 的商品不会被列出.";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button1
			// 
			this->button1->CausesValidation = false;
			this->button1->Location = System::Drawing::Point(257, 208);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(174, 103);
			this->button1->TabIndex = 3;
			this->button1->Text = L"添加";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &CommodityEntering::button1_Click);
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"微软雅黑", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(12, 317);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(33, 260);
			this->label2->TabIndex = 4;
			this->label2->Text = L"已\r\n添\r\n加\r\n的\r\n商\r\n品";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textBox1
			// 
			this->textBox1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->textBox1->CausesValidation = false;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"微软雅黑", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBox1->Location = System::Drawing::Point(257, 167);
			this->textBox1->Name = L"textBox1";
			this->textBox1->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->textBox1->Size = System::Drawing::Size(174, 35);
			this->textBox1->TabIndex = 5;
			this->textBox1->Text = L"1";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(887, 317);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(85, 50);
			this->button2->TabIndex = 6;
			this->button2->Text = L"删除";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &CommodityEntering::button2_Click);
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"微软雅黑", 13));
			this->label3->ForeColor = System::Drawing::Color::Black;
			this->label3->Location = System::Drawing::Point(883, 370);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(89, 207);
			this->label3->TabIndex = 7;
			this->label3->Text = L"若要放弃购买某项商品，选中该项, 并单击上方的\"删除\"按钮. 可多选.";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(767, 46);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(205, 65);
			this->button3->TabIndex = 8;
			this->button3->Text = L"已完成商品的添加或删除, 转入支付页面.";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &CommodityEntering::button3_Click);
			// 
			// button4
			// 
			this->button4->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button4->Location = System::Drawing::Point(767, 117);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(205, 65);
			this->button4->TabIndex = 9;
			this->button4->Text = L"放弃本次购物.";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoEllipsis = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->CausesValidation = false;
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(481, 12);
			this->label4->Margin = System::Windows::Forms::Padding(10);
			this->label4->Name = L"label4";
			this->label4->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label4->Size = System::Drawing::Size(495, 21);
			this->label4->TabIndex = 10;
			this->label4->Text = L"label4";
			// 
			// label5
			// 
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(616, 291);
			this->label5->Name = L"label5";
			this->label5->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label5->Size = System::Drawing::Size(269, 23);
			this->label5->TabIndex = 11;
			this->label5->Text = L"当前总交易额 / ￥: 0";
			// 
			// CommodityEntering
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 21);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size(984, 589);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->listView2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listView1);
			this->Font = (gcnew System::Drawing::Font(L"微软雅黑", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->ForeColor = System::Drawing::Color::Black;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(5);
			this->MaximizeBox = false;
			this->Name = L"CommodityEntering";
			this->Opacity = 0.98;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"添加或删除要购买的商品";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: property LCP::LeaguerSuite^ LeaguerSuite0;	
		// passed with the existing object immediately after this form constructed.
	public: property ArrayList^ ShoppingList;
	public: property ArrayList^ ShoppingListSended;
	private: 
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if( this->listView2->SelectedItems->Count > 0 && Convert::ToInt32(textBox1->Text) > 0 )
			{
				if(this->listView1->Items->Count > 0)
				{
					if( this->listView1->FindItemWithText(this->listView2->SelectedItems[0]->Text, false, 0, false) == nullptr )
					{
						// check out whether the commodityID already existed in listView1.
						//
						int selectedID = Convert::ToUInt32(this->listView2->SelectedItems[0]->Text);
						// continue to finish the "add" algorithm.
						SqlClient::SqlDataAdapter^ commodityAdapter = gcnew SqlClient::SqlDataAdapter( "SELECT * FROM dbo.CommodityInfo AS dc WHERE dc.CommodityID=" + this->listView2->SelectedItems[0]->Text, gcnew SqlConnection("Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;") );
						DataSet^ commoditySet = gcnew DataSet();
						commodityAdapter->Fill(commoditySet, "CommodityInfo");
						//
						// next.
						//
						SqlClient::SqlDataAdapter^ stockAdapter = gcnew SqlClient::SqlDataAdapter( "SELECT * FROM dbo.Stock AS ds WHERE ds.CommodityID=" + this->listView2->SelectedItems[0]->Text, gcnew SqlConnection("Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;") );
						DataSet^ stockSet = gcnew DataSet();
						stockAdapter->Fill(stockSet, "Stock");
						//
						// add to listView1, ShoppingList.
						// then textbox1's number <= stock ? 
						//
						if( Convert::ToUInt32(textBox1->Text) <= Convert::ToUInt32(stockSet->Tables["Stock"]->Rows[0]["Stock"]) )
						{
							DataRow^ tmpRow = commoditySet->Tables["CommodityInfo"]->Rows[0];
							int presentCount = 0;
							if( Convert::ToUInt32(tmpRow["PresentBaseNumber"]) != 0 )
							{
								presentCount = Convert::ToUInt32(textBox1->Text) / Convert::ToUInt32(
													tmpRow["PresentBaseNumber"])
													* Convert::ToUInt32(tmpRow["PresentRehovedNumber"]);
							}							 
							if( presentCount + Convert::ToUInt32(textBox1->Text) 
									> Convert::ToUInt32(stockSet->Tables["Stock"]->Rows[0]["Stock"]) ) 
							{
								System::Media::SystemSounds::Exclamation->Play();
								MessageBox::Show(L"欲购数量和赠品数量之和超出库存.");
							}
							else
							{
								this->ShoppingList->Add( gcnew LCP::DealSuite(commoditySet, stockSet,
																commodityAdapter,stockAdapter,
																Convert::ToUInt32(this->textBox1->Text), 
																Convert::ToUInt32(stockSet->Tables["Stock"]->Rows[0]["Stock"])) );
								String^ rehovedDealAmountStr = 
									(Convert::ToDouble(LCP::PaymentMode::RehovedDealAmount) / 100).ToString("F2");
								this->label5->Text = L"当前总交易额 / ￥: " + rehovedDealAmountStr;
								//
								// deal with decimal points.
								//
								String^ priceStr = (Convert::ToDouble(Convert::ToUInt32(tmpRow["Price"])) / 100).ToString("F2");
								int rehovedPayInt = Convert::ToUInt32(tmpRow["Price"]) * Convert::ToUInt32(textBox1->Text)
														* Convert::ToUInt32(tmpRow["Discount"]) / 10;
								String^ rehovedPayStr = (Convert::ToDouble(rehovedPayInt) / 100).ToString("F2");
								//
								// more preparations.
								//
								String^ commoditySort = "";
								if( tmpRow["CommoditySort"]->ToString()[2] == 'N' ) commoditySort = L"一般类";
								else if( tmpRow["CommoditySort"]->ToString()[2] == 'R' ) commoditySort = L"文体类";
								else if( tmpRow["CommoditySort"]->ToString()[2] == 'L' ) commoditySort = L"奢侈类";
								else if( tmpRow["CommoditySort"]->ToString()[1] == 'N' ) commoditySort = L"一般类";
								else if( tmpRow["CommoditySort"]->ToString()[1] == 'R' ) commoditySort = L"文体类";
								else if( tmpRow["CommoditySort"]->ToString()[1] == 'L' ) commoditySort = L"奢侈类";
								String^ presentString;
								if( Convert::ToUInt32(tmpRow["PresentBaseNumber"]) != 0 )
								{
									presentString = "买" + tmpRow["PresentBaseNumber"] + "赠" + tmpRow["PresentRehovedNumber"];
								}
								else
								{
									presentString = "无赠品";
								}
								ListViewItem^ tmpLVI = gcnew ListViewItem( gcnew cli::array<System::String^>(9) 
								{ // then go.
									tmpRow["CommodityID"]->ToString(), tmpRow["Name"]->ToString(), 
									priceStr, tmpRow["Discount"]->ToString(),	// formatting this  .
									textBox1->Text,								// 测试商品1 bug.
									rehovedPayStr, presentString, presentCount.ToString(), commoditySort 
								}, -1 );	
								this->listView1->Items->AddRange( gcnew cli::array<ListViewItem^>(1) {tmpLVI} );
							}
						}
						else
						{
							System::Media::SystemSounds::Exclamation->Play();
							MessageBox::Show(L"库存不足.");
							delete commodityAdapter, commoditySet, stockAdapter, stockSet;
						}
					}
					else
					{
						System::Media::SystemSounds::Exclamation->Play();
						MessageBox::Show("此商品已添加, 若要修改数量, 先删除 \"已添加的商品\" 中的对应项.");
					}
				}
				else
				{
					if( this->listView1->FindItemWithText(this->listView2->SelectedItems[0]->Text) == nullptr )
					{
						// check out whether the commodityID already existed in listView1.
						int selectedID = Convert::ToUInt32(this->listView2->SelectedItems[0]->Text);
						//
						// continue to finish the "add" algorithm.
						//
						SqlClient::SqlDataAdapter^ commodityAdapter = gcnew SqlClient::SqlDataAdapter( "SELECT * FROM dbo.CommodityInfo AS dc WHERE dc.CommodityID=" + this->listView2->SelectedItems[0]->Text, gcnew SqlConnection("Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;") );
						DataSet^ commoditySet = gcnew DataSet();
						commodityAdapter->Fill(commoditySet, "CommodityInfo");
						//
						// next.
						//
						SqlClient::SqlDataAdapter^ stockAdapter = gcnew SqlClient::SqlDataAdapter( "SELECT * FROM dbo.Stock AS ds WHERE ds.CommodityID=" + this->listView2->SelectedItems[0]->Text, gcnew SqlConnection("Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;") );
						DataSet^ stockSet = gcnew DataSet();
						stockAdapter->Fill(stockSet, "Stock");
						//
						// add to listView1, ShoppingList.
						// then textbox1's number <= stock ? 
						//
						if( Convert::ToUInt32(textBox1->Text) <= Convert::ToUInt32(stockSet->Tables["Stock"]->Rows[0]["Stock"]) )
						{
							DataRow^ tmpRow = commoditySet->Tables["CommodityInfo"]->Rows[0];
							int presentCount = 0;
							if( Convert::ToUInt32(tmpRow["PresentBaseNumber"]) != 0 )
							{
								presentCount = Convert::ToUInt32(textBox1->Text) / Convert::ToUInt32(
													tmpRow["PresentBaseNumber"])
													* Convert::ToUInt32(tmpRow["PresentRehovedNumber"]);
							}
							if( presentCount + Convert::ToUInt32(textBox1->Text) 
									> Convert::ToUInt32(stockSet->Tables["Stock"]->Rows[0]["Stock"]) ) 
							{
								System::Media::SystemSounds::Exclamation->Play();
								MessageBox::Show(L"欲购数量和赠品数量之和超出库存.");
							}
							else
							{
								this->ShoppingList->Add( gcnew LCP::DealSuite(commoditySet, stockSet,
																commodityAdapter,stockAdapter,
																Convert::ToUInt32(this->textBox1->Text), 
																Convert::ToUInt32(stockSet->Tables["Stock"]->Rows[0]["Stock"])) );
								String^ rehovedDealAmountStr = 
									(Convert::ToDouble(LCP::PaymentMode::RehovedDealAmount) / 100).ToString("F2");
								this->label5->Text = L"当前总交易额 / ￥: " + rehovedDealAmountStr;
								//
								// deal with decimal points.
								//
								String^ priceStr = (Convert::ToDouble(Convert::ToUInt32(tmpRow["Price"])) / 100).ToString("F2");
								int rehovedPayInt = Convert::ToUInt32(tmpRow["Price"]) * Convert::ToUInt32(textBox1->Text)
									* Convert::ToUInt32(tmpRow["Discount"]) / 10;
								String^ rehovedPayStr = (Convert::ToDouble(rehovedPayInt) / 100).ToString("F2");
								//
								// more preparations.
								//
								String^ commoditySort = "";
								if( tmpRow["CommoditySort"]->ToString()[2] == 'N' ) commoditySort = L"一般类";
								else if( tmpRow["CommoditySort"]->ToString()[2] == 'R' ) commoditySort = L"文体类";
								else if( tmpRow["CommoditySort"]->ToString()[2] == 'L' ) commoditySort = L"奢侈类";
								else if( tmpRow["CommoditySort"]->ToString()[1] == 'N' ) commoditySort = L"一般类";
								else if( tmpRow["CommoditySort"]->ToString()[1] == 'R' ) commoditySort = L"文体类";
								else if( tmpRow["CommoditySort"]->ToString()[1] == 'L' ) commoditySort = L"奢侈类";
								String^ presentString;
								if( Convert::ToUInt32(tmpRow["PresentBaseNumber"]) != 0 )
								{
									presentString = "买" + tmpRow["PresentBaseNumber"] + "赠" + tmpRow["PresentRehovedNumber"];
								}
								else
								{
									presentString = "无赠品.";
								}
								ListViewItem^ tmpLVI = gcnew ListViewItem( gcnew cli::array<System::String^>(9) 
								{ // then go.
									tmpRow["CommodityID"]->ToString(), tmpRow["Name"]->ToString(), 
									priceStr, tmpRow["Discount"]->ToString(),	// formatting this  .
									textBox1->Text,								// 测试商品1 bug.
									rehovedPayStr, presentString, presentCount.ToString(), commoditySort 
								}, -1 );	
								this->listView1->Items->AddRange( gcnew cli::array<ListViewItem^>(1) {tmpLVI} );
							}
						}
						else
						{
							System::Media::SystemSounds::Exclamation->Play();
							MessageBox::Show(L"库存不足.");
							delete commodityAdapter, commoditySet, stockAdapter, stockSet;
						}
					}
					else
					{
						System::Media::SystemSounds::Exclamation->Play();
						MessageBox::Show("此商品已添加, 若要修改数量, 先删除 \"已添加的商品\" 中的对应项.");
					}
				}
			}
		}
	private: 
		System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			int selectedCount = this->listView1->SelectedIndices->Count;
			if( selectedCount > 0 )
			{
				for( int i = 0; i < selectedCount; i ++ )
				{
					// what about ShoppingList ?
					// ^88^ regard them as the same at first, need to be tested. 
					// a bug here.
					//
					LCP::PaymentMode::RehovedDealAmount -= Convert::ToUInt32( Convert::ToDouble(
						this->listView1->Items[this->listView1->SelectedIndices[0]]->SubItems[5]->Text) * 100 );
					// Convert::ToUInt32( 
					// safe_cast<LCP::DealSuite^>(this->ShoppingList[this->listView1->SelectedIndices[0]])->commodity->Price * 
					// safe_cast<LCP::DealSuite^>(this->ShoppingList[this->listView1->SelectedIndices[0]])->paymentMode
						// ->CommodityQuantity );
					String^ rehovedDealAmountStr =
						(Convert::ToDouble(LCP::PaymentMode::RehovedDealAmount) / 100).ToString("F2");
					//	LCP::PaymentMode::RehovedDealAmount.ToString()
					//	->Substring(0, LCP::PaymentMode::RehovedDealAmount.ToString()->Length - 2) + "." 
					//	+ LCP::PaymentMode::RehovedDealAmount.ToString()
					//	->Substring(LCP::PaymentMode::RehovedDealAmount.ToString()->Length - 2, 2); // a bug here.
					//
					this->label5->Text = L"当前总交易额 / ￥: " + rehovedDealAmountStr;
					this->ShoppingList->RemoveAt(this->listView1->SelectedIndices[0]);
					this->listView1->Items->RemoveAt(this->listView1->SelectedIndices[0]);
				}
			}
		}
		// amount display. with an issue that struct DealSuite need changing.
		// blanks issues. then discount issues.
		// present overflow.
	private: 
		System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if( this->listView1->Items->Count > 0 )
			{
				// to copy arraylist.
				this->ShoppingListSended = safe_cast<ArrayList^>(this->ShoppingList->Clone());
				this->Hide();
				PayPage^ thePayPage = gcnew PayPage(this->LeaguerSuite0, this->ShoppingListSended);
				if( thePayPage->ShowDialog(this) == System::Windows::Forms::DialogResult::Cancel )
				{
					delete thePayPage;
					this->Show();
				}
				else
				{
					delete thePayPage;
					this->DialogResult = System::Windows::Forms::DialogResult::OK;
				}
			}
			else
			{
				System::Media::SystemSounds::Exclamation->Play();
				MessageBox::Show("尚未添加任何一项商品.");
			}
		}
};
}

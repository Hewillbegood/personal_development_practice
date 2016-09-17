#pragma once



namespace ATM_GH2005 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// RecordQuery 摘要
	/// </summary>
	public ref class RecordQuery : public System::Windows::Forms::Form
	{
	private: property LCP::LeaguerSuite^ LeaguerSuite0;
	public:
		RecordQuery(LCP::LeaguerSuite^ inLeaguerSuite)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
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
				this->label1->Text = "欢迎您, " + leaguerSortStr + " " + this->LeaguerSuite0->leaguer->FullName->Trim()
					+ L", 您的积分是 " +  Convert::ToDouble(this->LeaguerSuite0->leaguer->AccumulatePoints) / 100 + ".";
			}
			else
			{
				this->label1->Text = "欢迎您, " + leaguerSortStr + " " + this->LeaguerSuite0->leaguer->FullName + ".";
			}
			//
			// fill listView2 with all commodities' info WHERE the stack > 0.
			//
			SqlClient::SqlDataAdapter^ adapterForListV1 = gcnew SqlClient::SqlDataAdapter( "SELECT * FROM dbo.SalesLog AS dsl WHERE dsl.UserID=\'" + this->LeaguerSuite0->leaguer->UserID + "\'", gcnew SqlClient::SqlConnection("Data Source=127.0.0.1\\GH2005;Initial Catalog=ATM_GH2005;Integrated Security=false;User ID=sa;Password=B7204lb;") );
			//
			// test that problem. and begin at filling listView2.
			//
			DataTable^ dataTbForListV1 = gcnew DataTable();
			adapterForListV1->Fill(dataTbForListV1);
			for( int i = 0; i < dataTbForListV1->Rows->Count; i++ )
			{
				ListViewItem^ tmpLVI = gcnew ListViewItem( gcnew cli::array<System::String^>(4) {
					dataTbForListV1->Rows[i]["CommodityName"]->ToString(), 
					dataTbForListV1->Rows[i]["CommodityQuantity"]->ToString(),
					dataTbForListV1->Rows[i]["PresentQuantity"]->ToString(),
					dataTbForListV1->Rows[i]["DateTime"]->ToString(),
				}, -1 );
				this->listView1->Items->AddRange( gcnew cli::array<ListViewItem^>(1) {tmpLVI} );
			}
			this->listView1->MultiSelect = false;
		}
	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~RecordQuery()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ColumnHeader^  CommodityName;
	private: System::Windows::Forms::ColumnHeader^  CommodityQuantity;
	private: System::Windows::Forms::ColumnHeader^  PresentQuantity;
	private: System::Windows::Forms::ColumnHeader^  DateTime;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(RecordQuery::typeid));
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->CommodityName = (gcnew System::Windows::Forms::ColumnHeader());
			this->CommodityQuantity = (gcnew System::Windows::Forms::ColumnHeader());
			this->PresentQuantity = (gcnew System::Windows::Forms::ColumnHeader());
			this->DateTime = (gcnew System::Windows::Forms::ColumnHeader());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// listView1
			// 
			this->listView1->CausesValidation = false;
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->CommodityName, this->CommodityQuantity, 
				this->PresentQuantity, this->DateTime});
			this->listView1->FullRowSelect = true;
			this->listView1->GridLines = true;
			this->listView1->Location = System::Drawing::Point(39, 39);
			this->listView1->Margin = System::Windows::Forms::Padding(30);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(456, 418);
			this->listView1->TabIndex = 0;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// CommodityName
			// 
			this->CommodityName->Text = L"商品名称";
			this->CommodityName->Width = 166;
			// 
			// CommodityQuantity
			// 
			this->CommodityQuantity->Text = L"购买数量";
			this->CommodityQuantity->Width = 70;
			// 
			// PresentQuantity
			// 
			this->PresentQuantity->Text = L"赠品数量";
			this->PresentQuantity->Width = 62;
			// 
			// DateTime
			// 
			this->DateTime->Text = L"购买时间";
			this->DateTime->Width = 151;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"微软雅黑", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(62, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(460, 22);
			this->label1->TabIndex = 1;
			this->label1->Text = L"label1";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"微软雅黑", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label2->Location = System::Drawing::Point(37, 468);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(271, 20);
			this->label2->TabIndex = 2;
			this->label2->Text = L"注: 仅提供过去一个月内的购买记录的查询.";
			// 
			// button1
			// 
			this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button1->Location = System::Drawing::Point(393, 468);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(102, 27);
			this->button1->TabIndex = 3;
			this->button1->Text = L"返回";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// RecordQuery
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(534, 504);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->listView1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"RecordQuery";
			this->Text = L"购买记录查询";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}

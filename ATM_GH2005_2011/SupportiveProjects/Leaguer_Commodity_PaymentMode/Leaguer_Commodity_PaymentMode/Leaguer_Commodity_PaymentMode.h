// Leaguer_Commodity_PaymentMode.h
// struct DealSuite should be sorted. note: luxury && high-accPoints first. more details to be considered.
// Don't forget creditPay poundages.

#pragma once

namespace LCP {

	using namespace System;
	using namespace System::Data::SqlClient;
	using namespace System::Data;
	using namespace System::Collections;

	public enum class LeaguerType { Nope, Normal, VIP, Student, ViM_Student };
	public enum class CommodityType {		
		NormalPrice_NoPresent_RecreationAndSports,		// NNR
		NormalPrice_NoPresent_Luxury,
		NormalPrice_NoPresent_Neither,
		Discount_NoPresent_RecreationAndSports,			// DNR
		Discount_NoPresent_Luxury,
		Discount_NoPresent_Neither,
		PresentIncluded_RecreationAndSports,		// PR0
		PresentIncluded_Luxury,						// PL0
		PresentIncluded_Neither						// PN0
		//
		// logics between CommodityType and presentNumbers.
	};

	public ref class Commodity
	{
	private:
		unsigned int _commodityID;
		unsigned int _price;						// unit name: fen.
		unsigned int _discount;					// 10 represents no discount. No negative elements.
		unsigned int _accumulateMultiple;		// 1 represents no extra accumulate point. No negative elements.
		unsigned int _presentRehovedNumber;
		unsigned int _presentBaseNumber;
		System::String^ _name;
		CommodityType _sort;
	public:
		property System::String^ CommodityName
		{
			System::String^ get() { return _name; }
		}
		property unsigned int Price
		{
			unsigned int get() { return _price; }
		}
		property unsigned int Discount
		{
			unsigned int get() { return _discount; }
		}
		property unsigned int PresentRehovedNumber
		{
			unsigned int get() { return _presentRehovedNumber; }
		}
		property unsigned int PresentBaseNumber
		{
			unsigned int get() { return _presentBaseNumber; }
		}
		property CommodityType Sort
		{
			CommodityType get() { return _sort; }
		}
		property unsigned int AccumulateMultiple
		{
			unsigned int get() { return _accumulateMultiple; }
		}
		property unsigned int CommodityID
		{
			unsigned int get() { return _commodityID; }
		}
		Commodity(
			unsigned int inCommodityID, 
			unsigned int inPrice,
			unsigned int inDiscount,
			unsigned int inAccumulateMultiple,
			unsigned int inPresentRehovedNumber,
			unsigned int inPresentBaseNumber,
			System::String^ inName,
			System::String^ inCommoditySort
		)
			: _commodityID(inCommodityID), _price(inPrice), _discount(inDiscount), 
			  _accumulateMultiple(inAccumulateMultiple), _presentRehovedNumber(inPresentRehovedNumber),
			  _presentBaseNumber(inPresentBaseNumber), _name(inName)
		{
			switch(inCommoditySort[0])
			{
			case 'N': 
				switch(inCommoditySort[2])
				{
				case 'R': _sort = CommodityType::NormalPrice_NoPresent_RecreationAndSports; break;
				case 'L': _sort = CommodityType::NormalPrice_NoPresent_Luxury; break;
				case 'N': _sort = CommodityType::NormalPrice_NoPresent_Neither; break;
				}
				break;
			case 'D':
				switch(inCommoditySort[2])
				{
				case 'R': _sort = CommodityType::Discount_NoPresent_RecreationAndSports; break;
				case 'L': _sort = CommodityType::Discount_NoPresent_Luxury; break;
				case 'N': _sort = CommodityType::Discount_NoPresent_Neither; break;
				}
				break;
			case 'P':
				switch(inCommoditySort[1])
				{
				case 'R': _sort = CommodityType::PresentIncluded_RecreationAndSports; break;
				case 'L': _sort = CommodityType::PresentIncluded_Luxury; break;
				case 'N': _sort = CommodityType::PresentIncluded_Neither; break;
				}
				break;
			}
		}
	};

	public ref class PaymentMode
	{ // one to one Commodity.
	private:
		static int _rehovedDealAmount;						// unit name: fen.
		static int _realtimeSubmittedDealAmount;			// unit name: fen.
		static int _realtimeNeedFillingCreditAmount;		// unit name: fen.
		static int _realtimeNeedFillingCashAmount;			// unit name: fen.
		static int _realtimeNeedFillingVoncherAmount;		// unit name: fen.
		static int _realtimeNeedFillingAccPointsAmount;	// unit name: fen.
		static bool _cannotBuy;
		unsigned int _cashPay;						// unit name: fen.
		unsigned int _creditPay;						// unit name: fen.
		unsigned int _accumulatePointsPay;			// unit name: fen.
		unsigned int _voncherPay;						// unit name: fen.
		unsigned int _commodityQuantity;			// present quantity not included.
		unsigned int _presentQuantity;
		unsigned int _stock;
		Commodity^ _correspondingCommodity;
	public:
		static property int CreditPoundage;
		static property bool CannotBuy
		{ // don't forget to initialize it.
			bool get() { return _cannotBuy; }
			void set(bool inBool) { _cannotBuy = inBool; }
		}
		static property int RehovedDealAmount
		{
			int get() { return _rehovedDealAmount; }
			void set(int inDealAmount) { _rehovedDealAmount = inDealAmount; }
		}
		static property int RealtimeSubmittedDealAmount
		{
			int get() { return _realtimeSubmittedDealAmount; }
			void set(int inDealAmount) { _realtimeSubmittedDealAmount = inDealAmount; }
		}
		static property int RealtimeNeedFillingCreditAmount
		{
			int get() { return _realtimeNeedFillingCreditAmount; }
			void set(int inCreditAmount) { _realtimeNeedFillingCreditAmount = inCreditAmount; }
		}
		static property int RealtimeNeedFillingCashAmount
		{
			int get() { return _realtimeNeedFillingCashAmount; }
			void set(int inCashAmount) { _realtimeNeedFillingCashAmount = inCashAmount; }
		}
		static property int RealtimeNeedFillingVoncherAmount
		{
			int get() { return _realtimeNeedFillingVoncherAmount; }
			void set(int inVoncherAmount) { _realtimeNeedFillingVoncherAmount = inVoncherAmount; }
		}
		static property int RealtimeNeedFillingAccPointsAmount
		{
			int get() { return _realtimeNeedFillingAccPointsAmount; }
			void set(int inAccPointsAmount) { _realtimeNeedFillingAccPointsAmount = inAccPointsAmount; }
		}
		property unsigned int CashPay
		{
			unsigned int get() { return _cashPay; }
			void set(unsigned int inCashPay) { _cashPay = inCashPay; }
		}
		property unsigned int CreditPay
		{
			unsigned int get() { return _creditPay; }
			void set(unsigned int inCreditPay) { _creditPay = inCreditPay; }
		}
		property unsigned int AccumulatePointsPay
		{
			unsigned int get() { return _accumulatePointsPay; }
			void set(unsigned int inAccumulatePointsPay) { _accumulatePointsPay = inAccumulatePointsPay; }
		}
		property unsigned int VoncherPay
		{
			unsigned int get() { return _voncherPay; }
			void set(unsigned int inVoncherPay) { _voncherPay = inVoncherPay; }
		}
		property unsigned int CommodityQuantity
		{
			unsigned int get() { return _commodityQuantity; }
			void set(unsigned int inCommodityQuantity) { _commodityQuantity = inCommodityQuantity; }
		}
		property unsigned int PresentQuantity
		{
			unsigned int get() { return _presentQuantity; }
		}
		property unsigned int Stock
		{
			unsigned int get() { return _stock; }
			void set(unsigned int inStock) { _stock = inStock; }
		}
		property unsigned int TogetherPay;

		PaymentMode(unsigned int inCommodityQuantity, Commodity^ inCommodity, unsigned int inStock)
			: _cashPay(0), _creditPay(0), _accumulatePointsPay(0), _voncherPay(0), _presentQuantity(0),
			  _commodityQuantity(inCommodityQuantity), _correspondingCommodity(inCommodity), _stock(inStock)
		{
			TogetherPay = inCommodity->Price * inCommodityQuantity * inCommodity->Discount / 10;
			_rehovedDealAmount += this->TogetherPay;
			if(inCommodity->PresentBaseNumber != 0)
			{
				int multiple = inCommodityQuantity / inCommodity->PresentBaseNumber;
				_presentQuantity = inCommodity->PresentRehovedNumber * multiple;
			}
		}

		void FillPayments(LeaguerType inLeaguerSort, Commodity^ inCommodity)
		{
			switch(inLeaguerSort)
			{ // note the CommodityQuantity.
			case LeaguerType::Nope:
			case LeaguerType::Normal:
			case LeaguerType::Student:
				if(
					inCommodity->Sort == CommodityType::NormalPrice_NoPresent_Luxury ||
					inCommodity->Sort == CommodityType::Discount_NoPresent_Luxury ||
					inCommodity->Sort == CommodityType::PresentIncluded_Luxury
				)
				{
					int rehovedPay = inCommodity->Price * _commodityQuantity * inCommodity->Discount / 10;
					int convCreditPay = rehovedPay - _realtimeNeedFillingCashAmount;
					int convAccPointsPay = convCreditPay - _realtimeNeedFillingCreditAmount;
					if(_realtimeNeedFillingCashAmount >= rehovedPay)
					{
						_cashPay = rehovedPay;
						_realtimeNeedFillingCashAmount -= rehovedPay;
					}
					else if(_realtimeNeedFillingCreditAmount >= convCreditPay)
					{
						_cashPay =  _realtimeNeedFillingCashAmount;
						_realtimeNeedFillingCashAmount = 0;
						_creditPay = convCreditPay;
						_realtimeNeedFillingCreditAmount -= convCreditPay;
					}
					else if(_realtimeNeedFillingAccPointsAmount >= convAccPointsPay)
					{
						_cashPay = _realtimeNeedFillingCashAmount;
						_realtimeNeedFillingCashAmount = 0;
						_creditPay = _realtimeNeedFillingCreditAmount;
						_realtimeNeedFillingCreditAmount = 0;
						_accumulatePointsPay = convAccPointsPay;
						_realtimeNeedFillingAccPointsAmount -= convAccPointsPay;
					}
					else
					{
						_cannotBuy = true;
					}
				}
				else
				{
					int rehovedPay = inCommodity->Price * _commodityQuantity * inCommodity->Discount / 10;
					int convCreditPay = rehovedPay - _realtimeNeedFillingCashAmount;
					int convVoncherPay = convCreditPay - _realtimeNeedFillingCreditAmount;
					int convAccPointsPay = convVoncherPay - _realtimeNeedFillingVoncherAmount;
					if(_realtimeNeedFillingCashAmount >= rehovedPay)
					{
						_cashPay = rehovedPay;
						_realtimeNeedFillingCashAmount -= rehovedPay;
					}
					else if(_realtimeNeedFillingCreditAmount >= convCreditPay)
					{
						_cashPay =  _realtimeNeedFillingCashAmount;
						_realtimeNeedFillingCashAmount = 0;
						_creditPay = convCreditPay;
						_realtimeNeedFillingCreditAmount -= convCreditPay;
					}
					else if(_realtimeNeedFillingVoncherAmount >= convVoncherPay)
					{
						_cashPay = _realtimeNeedFillingCashAmount;
						_realtimeNeedFillingCashAmount = 0;
						_creditPay = _realtimeNeedFillingCreditAmount;
						_realtimeNeedFillingCreditAmount = 0;
						_voncherPay = convVoncherPay;
						_realtimeNeedFillingVoncherAmount -= convVoncherPay;
					}
					else
					{
						_cashPay = _realtimeNeedFillingCashAmount;
						_realtimeNeedFillingCashAmount = 0;
						_creditPay = _realtimeNeedFillingCreditAmount;
						_realtimeNeedFillingCreditAmount = 0;
						_voncherPay = _realtimeNeedFillingVoncherAmount;
						_realtimeNeedFillingVoncherAmount = 0;
						_accumulatePointsPay = convAccPointsPay;
						_realtimeNeedFillingAccPointsAmount -= convAccPointsPay;
					}
				}
				break;
			case LeaguerType::VIP:
			case LeaguerType::ViM_Student:
				{
					int rehovedPay = inCommodity->Price * _commodityQuantity * inCommodity->Discount / 10;
					int convCreditPay = rehovedPay - _realtimeNeedFillingCashAmount;
					int convVoncherPay = convCreditPay - _realtimeNeedFillingCreditAmount;
					int convAccPointsPay = convVoncherPay - _realtimeNeedFillingVoncherAmount;
					if(_realtimeNeedFillingCashAmount >= rehovedPay)
					{
						_cashPay = rehovedPay;
						_realtimeNeedFillingCashAmount -= rehovedPay;
					}
					else if(_realtimeNeedFillingCreditAmount >= convCreditPay)
					{
						_cashPay =  _realtimeNeedFillingCashAmount;
						_realtimeNeedFillingCashAmount = 0;
						_creditPay = convCreditPay;
						_realtimeNeedFillingCreditAmount -= convCreditPay;
					}
					else if(_realtimeNeedFillingVoncherAmount >= convVoncherPay)
					{
						_cashPay = _realtimeNeedFillingCashAmount;
						_realtimeNeedFillingCashAmount = 0;
						_creditPay = _realtimeNeedFillingCreditAmount;
						_realtimeNeedFillingCreditAmount = 0;
						_voncherPay = convVoncherPay;
						_realtimeNeedFillingVoncherAmount -= convVoncherPay;
					}
					else
					{
						_cashPay = _realtimeNeedFillingCashAmount;
						_realtimeNeedFillingCashAmount = 0;
						_creditPay = _realtimeNeedFillingCreditAmount;
						_realtimeNeedFillingCreditAmount = 0;
						_voncherPay = _realtimeNeedFillingVoncherAmount;
						_realtimeNeedFillingVoncherAmount = 0;
						_accumulatePointsPay = convAccPointsPay;
						_realtimeNeedFillingAccPointsAmount -= convAccPointsPay;
					}
				}
				break;
			}
		}
		// erase method.
		void ErasePaymentFills()
		{
			_cashPay = 0;
			_creditPay = 0;
			_voncherPay = 0;
			_accumulatePointsPay = 0;
		}
	};

	public ref class LeaguerBase
	{
	private:
		System::String^ _userID;
		System::String^ _fullName;
		System::String^ _passWord;
		System::String^ _certificate;
		unsigned int _accumulatePoints;		// unit name: fen.
		LeaguerType _sort;
	public:
		property System::String^ UserID
		{
			System::String^ get() { return _userID; }
			void set(System::String^ inStr) { _userID = inStr; }
		}
		property System::String^ PassWord
		{
			System::String^ get() { return _passWord; }
			void set(System::String^ inStr) { _passWord = inStr; }
		}
		property System::String^ FullName
		{
			System::String^ get() { return _fullName; }
			void set(System::String^ inStr) { _fullName = inStr; }
		}
		property unsigned int AccumulatePoints
		{
			unsigned int get() { return _accumulatePoints; }
			void set(unsigned int inInt) { _accumulatePoints = inInt; }
		}
		property LeaguerType Sort
		{ // read-only.
			LeaguerType get() { return _sort; };
		}

		virtual void UpdateAccumulatePoints(Commodity^ inCommodity, PaymentMode^ inPaymentMode) abstract;
		virtual void OddChangeUAP() abstract;

		LeaguerBase(
			System::String^ inUserID, System::String^ inFullName, System::String^ inPassWord, 
			System::String^ inCertificate, unsigned int inAccumulatePoints, LeaguerType inLeaguerSort		
		)	
			: _userID(inUserID), _fullName(inFullName), _passWord(inPassWord), _certificate(inCertificate),
			  _accumulatePoints(inAccumulatePoints), _sort(inLeaguerSort) {}
	};

	public ref class NotLeaguer : public LeaguerBase
	{
	public:
		NotLeaguer() : LeaguerBase("00NotLea", "¹Ë¿Í", "NotLeaguer", "00000", 0, LeaguerType::Nope) {}
		virtual void UpdateAccumulatePoints(Commodity^ inCommodity, PaymentMode^ inPaymentMode) override {}
		virtual void OddChangeUAP() override {}
	};

	public ref class NormalLeaguer : public LeaguerBase
	{
	public:
		NormalLeaguer(System::String^ inUserID, System::String^ inFullName, System::String^ inPassWord, 
			System::String^ inCertificate, unsigned int inAccumulatePoints)
		: LeaguerBase(inUserID, inFullName, inPassWord, inCertificate, inAccumulatePoints, LeaguerType::Normal) {}
		
		virtual void UpdateAccumulatePoints(Commodity^ inCommodity, PaymentMode^ inPaymentMode) override
		{ // one paymentmode object oriented.
			if(
				inCommodity->Sort == CommodityType::NormalPrice_NoPresent_Neither ||
				inCommodity->Sort == CommodityType::NormalPrice_NoPresent_Luxury
			)
			{
				AccumulatePoints += (inPaymentMode->CashPay + inPaymentMode->CreditPay) / 20 
									* inCommodity->AccumulateMultiple;
			}
			AccumulatePoints -= inPaymentMode->AccumulatePointsPay;
		}
		virtual void OddChangeUAP() override {}
	};

	public ref class VIP : public LeaguerBase
	{
	public:
		VIP( System::String^ inUserID, System::String^ inFullName, System::String^ inPassWord, 
				System::String^ inCertificate, unsigned int inAccumulatePoints )
		: LeaguerBase(inUserID, inFullName, inPassWord, inCertificate, inAccumulatePoints, LeaguerType::VIP) {}
		
		virtual void UpdateAccumulatePoints(Commodity^ inCommodity, PaymentMode^ inPaymentMode) override
		{ // note that this function should be invoked after all payment fills.
			if(
				inCommodity->Sort == CommodityType::NormalPrice_NoPresent_Neither ||
				inCommodity->Sort == CommodityType::NormalPrice_NoPresent_Luxury ||
				inCommodity->Sort == CommodityType::NormalPrice_NoPresent_RecreationAndSports
			)
			{
				AccumulatePoints += (inPaymentMode->CashPay + inPaymentMode->CreditPay 
									+ inPaymentMode->VoncherPay) / 10 * inCommodity->AccumulateMultiple;
			}
			else
			{
				AccumulatePoints += (inPaymentMode->CashPay + inPaymentMode->CreditPay
									+ inPaymentMode->VoncherPay) / 20 * inCommodity->AccumulateMultiple;
			}
			AccumulatePoints -= inPaymentMode->AccumulatePointsPay;
		}

		virtual void OddChangeUAP() override
		{ // only invoked once when all UpdateAccumulatePoints()s invoked.
			AccumulatePoints += PaymentMode::RealtimeNeedFillingVoncherAmount;
		}
	};

	public ref class Student : public LeaguerBase
	{
	private: String^ _school;
	public:
		Student( System::String^ inUserID, System::String^ inFullName, System::String^ inPassWord, 
						System::String^ inCertificate, unsigned int inAccumulatePoints, String^ inSchool )
			: LeaguerBase(inUserID, inFullName, inPassWord, inCertificate, inAccumulatePoints, LeaguerType::Student),
			  _school(inSchool) {}
		
		virtual void UpdateAccumulatePoints(Commodity^ inCommodity, PaymentMode^ inPaymentMode) override
		{ // one paymentmode object oriented.
			if(inCommodity->Sort == CommodityType::NormalPrice_NoPresent_RecreationAndSports)
			{
				AccumulatePoints += (inPaymentMode->CashPay + inPaymentMode->CreditPay) / 100 * 15
									* inCommodity->AccumulateMultiple + inPaymentMode->VoncherPay / 100 * 15;
			}
			else if(
				inCommodity->Sort == CommodityType::NormalPrice_NoPresent_Neither ||
				inCommodity->Sort == CommodityType::NormalPrice_NoPresent_Luxury ||
				inCommodity->Sort == CommodityType::Discount_NoPresent_RecreationAndSports
			)
			{
				AccumulatePoints += (inPaymentMode->CashPay + inPaymentMode->CreditPay) / 10
									* inCommodity->AccumulateMultiple + inPaymentMode->VoncherPay / 10;
			}
			else if(
				inCommodity->Sort == CommodityType::Discount_NoPresent_Neither ||
				inCommodity->Sort == CommodityType::Discount_NoPresent_Luxury ||
				inCommodity->Sort == CommodityType::PresentIncluded_RecreationAndSports
			)
			{
				AccumulatePoints += (inPaymentMode->CashPay + inPaymentMode->CreditPay) / 20
									* inCommodity->AccumulateMultiple + inPaymentMode->VoncherPay / 20;
			}
			AccumulatePoints -= inPaymentMode->AccumulatePointsPay;
		}
		virtual void OddChangeUAP() override {}
	};

	public ref class ViM_Student : public LeaguerBase
	{
	private: String^ _school;
	public:
		ViM_Student( System::String^ inUserID, System::String^ inFullName, System::String^ inPassWord, 
							System::String^ inCertificate, unsigned int inAccumulatePoints, String^ inSchool )
			: LeaguerBase(inUserID, inFullName, inPassWord, inCertificate, inAccumulatePoints, LeaguerType::ViM_Student), 
			  _school(inSchool) {}

		virtual void UpdateAccumulatePoints(Commodity^ inCommodity, PaymentMode^ inPaymentMode) override
		{ // one paymentmode object oriented.
			if(inCommodity->Sort == CommodityType::NormalPrice_NoPresent_RecreationAndSports)
			{
				AccumulatePoints += (inPaymentMode->CashPay + inPaymentMode->CreditPay 
										+ inPaymentMode->VoncherPay) / 100 * 15 * inCommodity->AccumulateMultiple;
			}
			else if( inCommodity->Sort == CommodityType::NormalPrice_NoPresent_Neither ||
				inCommodity->Sort == CommodityType::NormalPrice_NoPresent_Luxury ||
				inCommodity->Sort == CommodityType::Discount_NoPresent_RecreationAndSports ||
				inCommodity->Sort == CommodityType::PresentIncluded_RecreationAndSports )
			{
				AccumulatePoints += (inPaymentMode->CashPay + inPaymentMode->CreditPay 
										+ inPaymentMode->VoncherPay) / 10 * inCommodity->AccumulateMultiple;
			}
			else
			{
				AccumulatePoints += (inPaymentMode->CashPay + inPaymentMode->CreditPay 
										+ inPaymentMode->VoncherPay) / 20 * inCommodity->AccumulateMultiple;
			}
			AccumulatePoints -= inPaymentMode->AccumulatePointsPay;
		}
		// OddChangeUAP() remains to be tested.
		//
		virtual void OddChangeUAP() override
		{ // only invoked once when all UpdateAccumulatePoints()s invoked.
			AccumulatePoints += PaymentMode::RealtimeNeedFillingVoncherAmount;
		}
	};
	// a vital problem: messageboxes within the struct's namespace? this is complete mistake.
	public ref struct DealSuite
	{
		DataSet^ commodityInfoDS;
		DataSet^ stockDS;
		SqlDataAdapter^ commodityInfoDA;
		SqlDataAdapter^ stockDA;
		Commodity^ commodity;
		PaymentMode^ paymentMode;
		DealSuite( DataSet^ inCommInfoDS, DataSet^ inStockDS, SqlDataAdapter^ inCommInfoDA, SqlDataAdapter^ inStockDA,
						int inCommodityQuantity, int inStock )
			: commodityInfoDS(inCommInfoDS), stockDS(inStockDS), commodityInfoDA(inCommInfoDA), stockDA(inStockDA),
			  commodity( gcnew Commodity
			  (
				Convert::ToUInt32(commodityInfoDS->Tables["CommodityInfo"]->Rows[0]["CommodityID"]),
				Convert::ToUInt32(commodityInfoDS->Tables["CommodityInfo"]->Rows[0]["Price"]),
				Convert::ToUInt32(commodityInfoDS->Tables["CommodityInfo"]->Rows[0]["Discount"]),
				Convert::ToUInt32(commodityInfoDS->Tables["CommodityInfo"]->Rows[0]["AccumulateMultiple"]),
				Convert::ToUInt32(commodityInfoDS->Tables["CommodityInfo"]->Rows[0]["PresentRehovedNumber"]),
				Convert::ToUInt32(commodityInfoDS->Tables["CommodityInfo"]->Rows[0]["PresentBaseNumber"]),
				commodityInfoDS->Tables["CommodityInfo"]->Rows[0]["Name"]->ToString(),
				commodityInfoDS->Tables["CommodityInfo"]->Rows[0]["CommoditySort"]->ToString()
			  ) )
		{ 
			// paymentMode later. 
			// PaymentMode(unsigned int inCommodityQuantity, Commodity^ inCommodity, unsigned int inStock)
			paymentMode = gcnew PaymentMode(inCommodityQuantity, commodity, inStock);
		}
	};
	public ref struct LeaguerSuite
	{
		DataSet^ leaguerDS;
		SqlDataAdapter^ leaguerDA;	
		LeaguerBase^ leaguer;			
		LeaguerSuite(DataSet^ inLeaguerDS, SqlDataAdapter^ inLeaguerDA)
			: leaguerDS(inLeaguerDS), leaguerDA(inLeaguerDA)
		{ // Fill(..., "Leaguer") invoked.
			switch(leaguerDS->Tables["Leaguer"]->Rows[0]["LeaguerSort"]->ToString()[2])
			{
			case 'p':	leaguer = gcnew NotLeaguer(); break;
			case 'r':	leaguer = gcnew NormalLeaguer( leaguerDS->Tables["Leaguer"]->Rows[0]["UserID"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["FullName"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["PassWord"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["Certificate"]->ToString(),
									Convert::ToUInt32(leaguerDS->Tables["Leaguer"]->Rows[0]["AccumulatePoints"]) );
						break;
			case 'P':	leaguer = gcnew VIP( leaguerDS->Tables["Leaguer"]->Rows[0]["UserID"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["FullName"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["PassWord"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["Certificate"]->ToString(),
									Convert::ToUInt32(leaguerDS->Tables["Leaguer"]->Rows[0]["AccumulatePoints"]) );
						break;
			// enum class LeaguerType { Nope, Normal, VIP, Student, ViM_Student };
			// NormalLeaguer(System::String^ inUserID, System::String^ inFullName, System::String^ inPassWord, 
			// System::String^ inCertificate, unsigned int inAccumulatePoints)
			//
			case 'u':	leaguer = gcnew Student( leaguerDS->Tables["Leaguer"]->Rows[0]["UserID"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["FullName"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["PassWord"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["Certificate"]->ToString(),
									Convert::ToUInt32(leaguerDS->Tables["Leaguer"]->Rows[0]["AccumulatePoints"]),
									leaguerDS->Tables["Leaguer"]->Rows[0]["School"]->ToString() );
						break;
			case 'M':	leaguer = gcnew ViM_Student( leaguerDS->Tables["Leaguer"]->Rows[0]["UserID"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["FullName"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["PassWord"]->ToString(),
									leaguerDS->Tables["Leaguer"]->Rows[0]["Certificate"]->ToString(),
									Convert::ToUInt32(leaguerDS->Tables["Leaguer"]->Rows[0]["AccumulatePoints"]),
									leaguerDS->Tables["Leaguer"]->Rows[0]["School"]->ToString() );
						break;
			}
		}
	};
	// IComparer for LCP::LeaguerType::Nope.
	//
	public ref class ComparerForNope : public IComparer
	{
	private:
		virtual int Compare(Object^ obj0, Object^ obj1) sealed = IComparer::Compare
		{
			array<LCP::DealSuite^>^ dsArray = gcnew array<LCP::DealSuite^>(2)
				{ safe_cast<LCP::DealSuite^>(obj0), safe_cast<LCP::DealSuite^>(obj1) };
			if( (dsArray[0]->commodity->Sort == LCP::CommodityType::NormalPrice_NoPresent_Luxury
					|| dsArray[0]->commodity->Sort == LCP::CommodityType::Discount_NoPresent_Luxury
					|| dsArray[0]->commodity->Sort == LCP::CommodityType::PresentIncluded_Luxury) 
				&&
				(dsArray[1]->commodity->Sort != LCP::CommodityType::NormalPrice_NoPresent_Luxury
					&& dsArray[1]->commodity->Sort != LCP::CommodityType::Discount_NoPresent_Luxury
					&& dsArray[1]->commodity->Sort != LCP::CommodityType::PresentIncluded_Luxury) )
			{
				return -100;
			}
			else if( (dsArray[1]->commodity->Sort == LCP::CommodityType::NormalPrice_NoPresent_Luxury
					|| dsArray[1]->commodity->Sort == LCP::CommodityType::Discount_NoPresent_Luxury
					|| dsArray[1]->commodity->Sort == LCP::CommodityType::PresentIncluded_Luxury) 
				&&
				(dsArray[0]->commodity->Sort != LCP::CommodityType::NormalPrice_NoPresent_Luxury
					&& dsArray[0]->commodity->Sort != LCP::CommodityType::Discount_NoPresent_Luxury
					&& dsArray[0]->commodity->Sort != LCP::CommodityType::PresentIncluded_Luxury) )
			{
				return 100;
			}
			else
			{
				return 0;
			}
		}
	};

	public ref class ComparerForNormal : public IComparer
	{
	private:
		virtual int Compare(Object^ obj0, Object^ obj1) sealed = IComparer::Compare
		{
			array<LCP::DealSuite^>^ dsArray = gcnew array<LCP::DealSuite^>(2)
				{ safe_cast<LCP::DealSuite^>(obj0), safe_cast<LCP::DealSuite^>(obj1) };
			if( (dsArray[0]->commodity->Sort == LCP::CommodityType::NormalPrice_NoPresent_Luxury
					|| dsArray[0]->commodity->Sort == LCP::CommodityType::Discount_NoPresent_Luxury
					|| dsArray[0]->commodity->Sort == LCP::CommodityType::PresentIncluded_Luxury) 
				&&
				(dsArray[1]->commodity->Sort != LCP::CommodityType::NormalPrice_NoPresent_Luxury
					&& dsArray[1]->commodity->Sort != LCP::CommodityType::Discount_NoPresent_Luxury
					&& dsArray[1]->commodity->Sort != LCP::CommodityType::PresentIncluded_Luxury) )
			{
				return -100;
			}
			else if( (dsArray[1]->commodity->Sort == LCP::CommodityType::NormalPrice_NoPresent_Luxury
					|| dsArray[1]->commodity->Sort == LCP::CommodityType::Discount_NoPresent_Luxury
					|| dsArray[1]->commodity->Sort == LCP::CommodityType::PresentIncluded_Luxury) 
				&&
				(dsArray[0]->commodity->Sort != LCP::CommodityType::NormalPrice_NoPresent_Luxury
					&& dsArray[0]->commodity->Sort != LCP::CommodityType::Discount_NoPresent_Luxury
					&& dsArray[0]->commodity->Sort != LCP::CommodityType::PresentIncluded_Luxury) )
			{
				return 100;
			}
			else
			{
				int accumulateCoefficient[2] = {0, 0};
				for(int i=0; i<2; i++)
				{ /*		enum class CommodityType { NormalPrice_NoPresent_RecreationAndSports,		// NNR
							NormalPrice_NoPresent_Luxury,
							NormalPrice_NoPresent_Neither,
							Discount_NoPresent_RecreationAndSports,			// DNR
							Discount_NoPresent_Luxury,
							Discount_NoPresent_Neither,
							PresentIncluded_RecreationAndSports,		// PR0
							PresentIncluded_Luxury,						// PL0
							PresentIncluded_Neither						// PN0
							//
							// logics between CommodityType and presentNumbers. };	*/
					switch(dsArray[i]->commodity->Sort)
					{
					case LCP::CommodityType::NormalPrice_NoPresent_Neither:
					case LCP::CommodityType::NormalPrice_NoPresent_Luxury:
						accumulateCoefficient[i] = 5 / 100 * dsArray[i]->commodity->AccumulateMultiple;
						break;
					default:
						accumulateCoefficient[i] = 0;
						break;
					}
				}
				if( accumulateCoefficient[0] > accumulateCoefficient[1] )
				{
					return -100;
				}
				else if( accumulateCoefficient[0] < accumulateCoefficient[1] )
				{
					return 100;
				}
				else
				{
					return 0;
				}
			}
		}
	};

	public ref class ComparerForStudent : public IComparer
	{
	private:
		virtual int Compare(Object^ obj0, Object^ obj1) sealed = IComparer::Compare
		{
			array<LCP::DealSuite^>^ dsArray = gcnew array<LCP::DealSuite^>(2)
				{ safe_cast<LCP::DealSuite^>(obj0), safe_cast<LCP::DealSuite^>(obj1) };
			if( (dsArray[0]->commodity->Sort == LCP::CommodityType::NormalPrice_NoPresent_Luxury
					|| dsArray[0]->commodity->Sort == LCP::CommodityType::Discount_NoPresent_Luxury
					|| dsArray[0]->commodity->Sort == LCP::CommodityType::PresentIncluded_Luxury) 
				&&
				(dsArray[1]->commodity->Sort != LCP::CommodityType::NormalPrice_NoPresent_Luxury
					&& dsArray[1]->commodity->Sort != LCP::CommodityType::Discount_NoPresent_Luxury
					&& dsArray[1]->commodity->Sort != LCP::CommodityType::PresentIncluded_Luxury) )
			{
				return -100;
			}
			else if( (dsArray[1]->commodity->Sort == LCP::CommodityType::NormalPrice_NoPresent_Luxury
					|| dsArray[1]->commodity->Sort == LCP::CommodityType::Discount_NoPresent_Luxury
					|| dsArray[1]->commodity->Sort == LCP::CommodityType::PresentIncluded_Luxury) 
				&&
				(dsArray[0]->commodity->Sort != LCP::CommodityType::NormalPrice_NoPresent_Luxury
					&& dsArray[0]->commodity->Sort != LCP::CommodityType::Discount_NoPresent_Luxury
					&& dsArray[0]->commodity->Sort != LCP::CommodityType::PresentIncluded_Luxury) )
			{
				return 100;
			}
			else
			{
				int accumulateCoefficient[2] = {0, 0};
				for(int i=0; i<2; i++)
				{ // intertwined with laughing at and complaining about my algorithm for computing the accumulate points incoming of -
				// CommodityType::Student? well, if we develop science and technology to meet our greediest demand, hng, then ---
				// we'd better committe suicide at once, for the life will be A HELL.
					switch(dsArray[i]->commodity->Sort)
					{
					case LCP::CommodityType::NormalPrice_NoPresent_RecreationAndSports:
						accumulateCoefficient[i] = 15 / 100 * dsArray[i]->commodity->AccumulateMultiple;
						break;
					case LCP::CommodityType::NormalPrice_NoPresent_Neither:
					case LCP::CommodityType::NormalPrice_NoPresent_Luxury:
					case LCP::CommodityType::Discount_NoPresent_RecreationAndSports:
						accumulateCoefficient[i] = 10 / 100 * dsArray[i]->commodity->AccumulateMultiple;
						break;
					case LCP::CommodityType::Discount_NoPresent_Neither:
					case LCP::CommodityType::Discount_NoPresent_Luxury:
					case LCP::CommodityType::PresentIncluded_RecreationAndSports:
						accumulateCoefficient[i] = 5 / 100 * dsArray[i]->commodity->AccumulateMultiple;
						break;
					default:
						accumulateCoefficient[i] = 0;
						break;
					}
				}
				if( accumulateCoefficient[0] > accumulateCoefficient[1] )
				{
					return -100;
				}
				else if( accumulateCoefficient[0] < accumulateCoefficient[1] )
				{
					return 100;
				}
				else
				{
					return 0;
				}
			}
		}
	};
	
	public ref class ComparerForVIP : public IComparer
	{
	private:
		virtual int Compare(Object^ obj0, Object^ obj1) sealed = IComparer::Compare
		{
			array<LCP::DealSuite^>^ dsArray = gcnew array<LCP::DealSuite^>(2)
				{ safe_cast<LCP::DealSuite^>(obj0), safe_cast<LCP::DealSuite^>(obj1) };
			int accumulateCoefficient[2] = {0, 0};
			for(int i=0; i<2; i++)
			{ /*		enum class CommodityType { NormalPrice_NoPresent_RecreationAndSports,		// NNR
						NormalPrice_NoPresent_Luxury,
						NormalPrice_NoPresent_Neither,
						Discount_NoPresent_RecreationAndSports,			// DNR
						Discount_NoPresent_Luxury,
						Discount_NoPresent_Neither,
						PresentIncluded_RecreationAndSports,		// PR0
						PresentIncluded_Luxury,						// PL0
						PresentIncluded_Neither						// PN0
						//
						// logics between CommodityType and presentNumbers. };	*/
				switch(dsArray[i]->commodity->Sort)
				{
				case LCP::CommodityType::NormalPrice_NoPresent_RecreationAndSports:
				case LCP::CommodityType::NormalPrice_NoPresent_Luxury:
				case LCP::CommodityType::NormalPrice_NoPresent_Neither:
					accumulateCoefficient[i] = 10 / 100 * dsArray[i]->commodity->AccumulateMultiple;
					break;
				default:
					accumulateCoefficient[i] = 5 / 100 * dsArray[i]->commodity->AccumulateMultiple;
					break;
				}
			}
			if( accumulateCoefficient[0] > accumulateCoefficient[1] )
			{
				return -100;
			}
			else if( accumulateCoefficient[0] < accumulateCoefficient[1] )
			{
				return 100;
			}
			else
			{
				return 0;
			}
		}
	};

	public ref class ComparerForViM_Student : public IComparer
	{
	private:
		virtual int Compare(Object^ obj0, Object^ obj1) sealed = IComparer::Compare
		{
			array<LCP::DealSuite^>^ dsArray = gcnew array<LCP::DealSuite^>(2)
				{ safe_cast<LCP::DealSuite^>(obj0), safe_cast<LCP::DealSuite^>(obj1) };
			int accumulateCoefficient[2] = {0, 0};
			for(int i=0; i<2; i++)
			{ /*		enum class CommodityType { NormalPrice_NoPresent_RecreationAndSports,		// NNR
						NormalPrice_NoPresent_Luxury,
						NormalPrice_NoPresent_Neither,
						Discount_NoPresent_RecreationAndSports,			// DNR
						Discount_NoPresent_Luxury,
						Discount_NoPresent_Neither,
						PresentIncluded_RecreationAndSports,		// PR0
						PresentIncluded_Luxury,						// PL0
						PresentIncluded_Neither						// PN0
						//
						// logics between CommodityType and presentNumbers. };	*/
				switch(dsArray[i]->commodity->Sort)
				{
				case LCP::CommodityType::NormalPrice_NoPresent_RecreationAndSports:
					accumulateCoefficient[i] = 15 / 100 * dsArray[i]->commodity->AccumulateMultiple;
					break;
				case LCP::CommodityType::NormalPrice_NoPresent_Luxury:
				case LCP::CommodityType::NormalPrice_NoPresent_Neither:
				case LCP::CommodityType::Discount_NoPresent_RecreationAndSports:
				case LCP::CommodityType::PresentIncluded_RecreationAndSports:
					accumulateCoefficient[i] = 10 / 100 * dsArray[i]->commodity->AccumulateMultiple;
					break;
				default:
					accumulateCoefficient[i] = 5 / 100 * dsArray[i]->commodity->AccumulateMultiple;
					break;
				}
			}
			if( accumulateCoefficient[0] > accumulateCoefficient[1] )
			{
				return -100;
			}
			else if( accumulateCoefficient[0] < accumulateCoefficient[1] )
			{
				return 100;
			}
			else
			{
				return 0;
			}
		}
	}; 
}

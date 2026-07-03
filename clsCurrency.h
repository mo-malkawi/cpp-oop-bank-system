#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:

	enum enMode {EmptyMode = 0, UpdateMode = 1};
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrncyObject(string Line, string Seperator = "#//#")
	{
		vector <string> vCurrncyData = clsString::Split(Line,Seperator);

		return clsCurrency(enMode::UpdateMode,vCurrncyData[0],
			vCurrncyData[1], vCurrncyData[2], stof(vCurrncyData[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency , string Seperator = "#//#")
	{
		string CurrencyRecord = "";

		CurrencyRecord = Currency.CurrencyCountry() + Seperator;
		CurrencyRecord += Currency.CurrencyCode() + Seperator;
		CurrencyRecord += Currency.CurrencyName() + Seperator;
		CurrencyRecord += to_string(Currency.Rate());

		return CurrencyRecord;
	}

	static vector <clsCurrency> _LoadCurreniesDataFromFile()
	{
		vector <clsCurrency> _vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrncyObject(Line);
				_vCurrencies.push_back(Currency);
			}

			MyFile.close();

		}

		return _vCurrencies;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsCurrency& C : vCurrencies)
			{
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}

	}

	void _Update()
	{
		vector <clsCurrency> _vCurrencies;
		_vCurrencies = _LoadCurreniesDataFromFile();

		for (clsCurrency& C : _vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(_vCurrencies);

	}

public:

	clsCurrency(enMode Mode, string Country, string CurrneyCode,string CurrncyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrneyCode;
		_CurrencyName = CurrncyName;
		_Rate = Rate;
	}
	
	bool isEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string CurrencyCountry()
	{
		return _Country;
	}
	
	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrncyObject(Line);
				if (Currency.CurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
		}

	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrncyObject(Line);
				if (clsString::UpperAllString(Currency.CurrencyCountry()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}
		}

	}

	static bool DoesCurrencyExist(string CurrencyCode)
	{
		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);
		return (!C1.isEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurreniesDataFromFile();
	}

	float ConvertToUSD( float Amount)
	{
		return (Amount / Rate());
	}

	float ConvertToOtherCurrency(clsCurrency Currency, float Amount)
	{

		if (CurrencyCode() == "USD")
		{
			return Amount * Currency.Rate();
		}
		else
		{
			float AmountInUSD = ConvertToUSD(Amount);
			return AmountInUSD * Currency.Rate();
		}

	}


};


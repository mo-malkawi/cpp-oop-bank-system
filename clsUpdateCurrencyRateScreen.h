#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\n\nCurrency Card:\n";
		cout << "_________________________________\n";
		cout << "\nCountry      : " << Currency.CurrencyCountry();
		cout << "\nCode         : " << Currency.CurrencyCode();
		cout << "\nName         : " << Currency.CurrencyName();
		cout << "\nRate(1$) =   : " << Currency.Rate();
		cout << "\n_________________________________\n";

	}

	static float _ReadRate()
	{
		cout << "\n\nEnter new rate: ";
		float NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}

public:

	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("    Update Currency Rate Screen");

		cout << "\nPlease enter currency code: ";
		string CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::DoesCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrencyCard(Currency);

		cout << "\nAre you sure you want to update the rate of this currency? y/n ? ";
		char Answer = 'n';
		cin >> Answer;

		if (toupper(Answer) == 'N')
			return;
		
		cout << "\n\nUpdate Currency Rate:\n";
		cout << "__________________________";
		Currency.UpdateRate(_ReadRate());

		cout << "\nCurrency Rate Updated successfully :-)";
		_PrintCurrencyCard(Currency);

	}

};


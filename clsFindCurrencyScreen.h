#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen : public clsScreen
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

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.isEmpty())
		{
			cout << "\nCurrency Found :-)";
			_PrintCurrencyCard(Currency);
		}
		else
			cout << "\nCurrency as not found :-(";
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t Find Currency Screen");
		
		cout << "\nFind by: [1] Code or [2] Country ? ";
		short Answer = clsInputValidate::ReadShortNumberBetween(1, 2, "Choose between 1 and 2 !!!\n");

		if (Answer == 1)
		{
			string CurrencyCode;
			cout << "\nPlease enter currency code: ";
			CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
		}
		else
		{
			string CurrencyCountry;
			cout << "\nPlease enter currency Country: ";
			CurrencyCountry = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(CurrencyCountry);
			_ShowResults(Currency);
		}



	}

};


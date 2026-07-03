#pragma once
#include "clsScreen.h"
class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	static void _PrintCurrencyCard(clsCurrency &Currency1 , string Title = "Currency Card")
	{
		cout << endl << Title ;
		cout << "\n_________________________________\n";
		cout << "\nCountry      : " << Currency1.CurrencyCountry();
		cout << "\nCode         : " << Currency1.CurrencyCode();
		cout << "\nName         : " << Currency1.CurrencyName();
		cout << "\nRate(1$) =   : " << Currency1.Rate();
		cout << "\n_________________________________\n";

	}

	static float _ReadAmount()
	{
		cout << "\nEnter amount to exchange: ";
		float Amount = clsInputValidate::ReadFloatNumber();

		return Amount;
	}

	static clsCurrency _GetCurrency(string Message)
	{
		string CurrencyCode;
		cout << Message << endl;

		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::DoesCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		return clsCurrency::FindByCode(CurrencyCode);
	}

	static void _PrintCalculationsResults(float Amount,clsCurrency Currency1,clsCurrency Currency2)
	{
		_PrintCurrencyCard(Currency1, "Convert from:");

		float AmountInUSD = Currency1.ConvertToUSD(Amount);

		if(Currency1.CurrencyCode() != "USD")
		cout << endl << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInUSD << " USD\n";

		if (Currency2.CurrencyCode() == "USD")
			return;

		_PrintCurrencyCard(Currency2, "\nConverting from USD to:\n");

		float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Currency2, Amount);

		cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInCurrency2 << " ";
		cout << Currency2.CurrencyCode();

	}

public:
	static void ShowCurrencyCalculatorScreen()
	{
		

		char Continue = 'Y';

		while (toupper(Continue) == 'Y')
		{
			system("cls");
			_DrawScreenHeader("\t Currency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease enter currency 1 code: ");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease enter currency 2 code: ");
			float Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo you want to perform another calculation? y/n ?";
			cin >> Continue;
		}


	}
};


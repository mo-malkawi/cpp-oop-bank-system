#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include <vector>

class clsCurrenciesListScreen : protected clsScreen
{
private:
	static void _PrintCurrencyRecord(clsCurrency Currency)
	{
		cout << setw(8) << left << "" << "| " << left << setw(32) << Currency.CurrencyCountry() ;
		cout << "| " << left << setw(10) << Currency.CurrencyCode();
		cout << "| " << left << setw(37) << Currency.CurrencyName();
		cout << "| " << left << setw(15) << Currency.Rate() << endl;
	}

public:

	static void ShowCurrenciesListScreen()
	{
		system("cls");
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();
		string Title = "\t Currencies List Screen";
		string SubTitle = "\t (" + to_string(vCurrencies.size()) + ") Currencies.";

		_DrawScreenHeader(Title,SubTitle);



		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(32) << "Country";
		cout << "| " << left << setw(10) << "Code";
		cout << "| " << left << setw(37) << "Name";
		cout << "| " << left << setw(15) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		if (vCurrencies.empty())
		{
			cout << "\t\t\t\tNo Currencies available in the sysytem! \n";
		}
		else
		{
			for (clsCurrency& C : vCurrencies)
			{
				_PrintCurrencyRecord(C);
			}
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}
};


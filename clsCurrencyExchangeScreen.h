#pragma once
#include "clsScreen.h"
#include "iomanip"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
    
    enum enCurrencyExchangeMenuOption {
        eListCurrencies = 1 , eFindCurrency = 2, eUpdateRate = 3,
        eCurrenyCalculator = 4 , eMainMenu = 5
    };

    static short _ReadCurrencyExchangeScreenMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what you want to do [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 and 5 !");
        return Choice;
    }

    static void _ShowListCurrenciesScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
        
    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _GoBackToCurrencyExchangeMenu()
    {
        cout << "\n\nPress any key to go back to Currency Exchange Menu...";
        system("pause>0");
        ShowCurrencyExchangeMenu();
    }

    static void _PerformCurrencyExchangeMenuOption
    (enCurrencyExchangeMenuOption CurrencyExchangeMenuOption)
    {
        switch (CurrencyExchangeMenuOption)
        {
        case enCurrencyExchangeMenuOption::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenu();
            break;
        }
        case enCurrencyExchangeMenuOption::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenu();
            break;
        }
        case enCurrencyExchangeMenuOption::eUpdateRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrencyExchangeMenu();
            break;
        }
        case enCurrencyExchangeMenuOption::eCurrenyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenu();
            break;
        }
        case enCurrencyExchangeMenuOption::eMainMenu:
        {

        }
        }

    }

public:
	static void ShowCurrencyExchangeMenu()
	{
        system("cls");
		_DrawScreenHeader("     Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currncy Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyExchangeMenuOption
        (enCurrencyExchangeMenuOption(_ReadCurrencyExchangeScreenMenuOption()));

	}

};


#pragma once
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "Global.h"


class clsLoginScreen : protected clsScreen
{
private:
	static bool _Login()
	{
		bool LoginFailed = false;
		short LoginFailedCount = 0;

		string Username, Password;

		do
		{
			

			if (LoginFailed)
			{
				LoginFailedCount++;
				cout << "\nInvalid Username/Password!";
				cout << "\nYou have " << 3 - LoginFailedCount << " trial(s) to login.\n";
			}

			if (LoginFailedCount == 3)
			{
				cout << "\nYou are locked after 3 failed trials.\n";
				return false;
			}

			cout << "\nEnter Username: ";
			cin >> Username;

			cout << "Enter Password: ";
			cin >> Password;

			CurrentUser = clsUser::Find(Username, Password);

			LoginFailed = CurrentUser.IsEmpty();


		} while (LoginFailed);

		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenu();
		return true;

	}


public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t    Login Screen");
		return _Login();
		
	}
};


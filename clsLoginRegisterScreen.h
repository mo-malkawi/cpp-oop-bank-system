#pragma once
#include "clsScreen.h"
#include "clsUser.h"
class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintRegistrationRecord(clsUser::stLoginRegisterRecord Registration)
	{

		cout << "\n\t" << "| " << setw(37) << left << Registration.DataTime;
		cout << "| " << setw(25) << left << Registration.Username;
		cout << "| " << setw(25) << left << Registration.Password;
		cout << "| " << Registration.Permissions;
	}


public:

	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
		{
			return;// this will exit the function and it will not continue
		}

		vector <clsUser::stLoginRegisterRecord> vRegistrations = clsUser::GetLoginRegisterList();

		string Title = "\tLogin Register List Screen";
		string SubTitle = "\t     (" + to_string(vRegistrations.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << "\n\n\t" << "_______________________________________________";
		cout << "______________________________________________________\n";
		cout << "\n\t" << "| " << setw(37) << left << "Date/Time";
		cout << "| "<< setw(25) << left << "Username";
		cout << "| "<< setw(25) << left << "Password";
		cout << "| "<< "Permissions";
		cout << "\n\t" << "_______________________________________________";
		cout << "______________________________________________________\n";

		if (vRegistrations.size() == 0)
			cout << "\n\t\t\t\t\tLogin Register is empty !!!\n";
		else
		{
			for (clsUser::stLoginRegisterRecord& Reg : vRegistrations)
			{
				_PrintRegistrationRecord(Reg);
			}
		}


		cout << "\n\t" << "_______________________________________________";
		cout << "______________________________________________________\n";

	}
};


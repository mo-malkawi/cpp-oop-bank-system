#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{

		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

	static string _ReadAccountNumber(string Message)
	{
		cout << Message;
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n\nClient with account number[" << AccountNumber << "] does not exist,";
			cout << "enter another account number: ";
			cin >> AccountNumber;
		}

		return AccountNumber;
	}

	static double ReadAmount(clsBankClient &SourceClient)
	{
		double TransferAmount = 0;
		cout << "\n\nEnter transfer amount: ";
		TransferAmount = clsInputValidate::ReadDblNumberBetween(0, SourceClient.AccountBalance,
			"Amount exceeds the available balance, enter transfer amount again: ");

		return TransferAmount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t   Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\n\nEnter account number to transfer from: "));

		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\n\nEnter account number to transfer To: "));

		_PrintClient(DestinationClient);

		double TransferAmount = ReadAmount(SourceClient);

		char Answer = 'n';
		cout << "\nAre you sure you want to perform this operation? Y/N ?";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (SourceClient.Transfer(TransferAmount, DestinationClient))
			{
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer Failed\n";
			}
			
		}
		else
		{
			cout << "\nOperation was cancelled\n";
		}

		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);

	}

};


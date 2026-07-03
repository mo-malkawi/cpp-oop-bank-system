#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen : public clsScreen
{
private:

    static void _PrintTransferRecord(clsBankClient::stTrasnferLogRecord Record)
    {
        cout << "\n\t" << "| " << setw(25) << left << Record.DateTime;
        cout << "| " << setw(8) << left << Record.SourceAccNumber;
        cout << "| " << setw(8) << left << Record.DestinationAccNumber;
        cout << "| " << setw(12) << left << Record.TransferAmount;
        cout << "| " << setw(15) << left << Record.SourceBalance;
        cout << "| " << setw(15) << left << Record.DestinationBalance;
        cout << "| " << setw(12) << left << Record.User;
    }


public:

    static void ShowTransferLogScreen()
    {
        vector <clsBankClient::stTrasnferLogRecord> TransferLog = clsBankClient::GetTransferLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    ("+to_string(TransferLog.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << "\n\n\t" << "_______________________________________________";
        cout << "_________________________________________________________\n";
        cout << "\n\t" << "| " << setw(25) << left << "Date/Time";
        cout << "| " << setw(8) << left << "s.Acct";
        cout << "| " << setw(8) << left << "d.Acct";
        cout << "| " << setw(12) << left << "Amount";
        cout << "| " << setw(15) << left << "s.Balance";
        cout << "| " << setw(15) << left << "d.Balance";
        cout << "| " << setw(12) << left << "d.User";
        cout << "\n\t" << "_______________________________________________";
        cout << "_________________________________________________________\n";



        if (TransferLog.size() == 0)
            cout << "\t\t\t\tTransfer Log is empty!!!!\n";
        else
        {
            for (clsBankClient::stTrasnferLogRecord &Record : TransferLog)
            {
                _PrintTransferRecord(Record);
            }
        }

        cout << "\n\t" << "_______________________________________________";
        cout << "_________________________________________________________\n";

    }


};


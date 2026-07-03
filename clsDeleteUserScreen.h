#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.Username;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\t  Delete User Screen");

        string Username = "";

        cout << "\nPlease enter username: ";
        Username = clsInputValidate::ReadString();

        while (!clsUser::DoesUserExist(Username))
        {
            cout << "\nUser is not found, choose another one: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(Username);
        _PrintUser(User1);

        cout << "\nAre you sure you want to delete this user? Y/N  ";

        char Answer = 'n';
        cin >> Answer;
        
        Answer = tolower(Answer);

        if (Answer == 'y')
        {
            if (User1.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\nError User was not deleted\n";
            }
        }


    }
};


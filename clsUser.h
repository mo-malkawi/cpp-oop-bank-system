#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include <fstream>

class clsUser : public clsPerson
{
private:
	enum enMode{EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2};
	enMode _Mode;
	string _Username;
	string _Password;
	int _Permissions;
	bool _MarkedForDeletion = false;

	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertRegisterLineToRecord(string Line , string Seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);

		LoginRegisterRecord.DataTime = LoginRegisterDataLine.at(0);
		LoginRegisterRecord.Username = LoginRegisterDataLine.at(1);
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine.at(2));
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine.at(3));

		return LoginRegisterRecord;

	}

	string _PrepareLoginRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += Username + Seperator;
		LoginRecord += clsUtil::EncryptText(Password) + Seperator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;

	}


	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
	{
		vector <string> vUserData;
		vUserData = clsString::Split(Line,Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string UserRecord = "";

		UserRecord = User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.Username + Seperator;
		UserRecord += clsUtil::EncryptText(User.Password) + Seperator;
		UserRecord += to_string(User.Permissions);
		
		return UserRecord;
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				vUsers.push_back(User);
			}

			MyFile.close();
		}
		return vUsers;
	}

	void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsUser& User : vUsers)
			{
				if(User.MarkedForDeletion() == false)
				{
					DataLine = _ConvertUserObjectToLine(User);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.Username == _Username)
			{
				U = *this;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			
			MyFile.close();
		}
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}



public:
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8,
		pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLoginRegister = 128
		,pCurrencyExchange = 256
	};

	clsUser(enMode Mode,string FirstName,string LastName,
		string Email,string Phone,	string Username,string Password,
		int Permissions) :
		clsPerson(FirstName, LastName ,Email,Phone )
	{
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	struct stLoginRegisterRecord
	{
		string DataTime;
		string Username;
		string Password;
		short Permissions;
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeletion()
	{
		return _MarkedForDeletion;
	}

	void setUsername(string Username)
	{
		_Username = Username;
	}
	string getUsername()
	{
		return _Username;
	}
	__declspec(property(get = getUsername, put = setUsername))string Username;

	void setPassword(string Password)
	{
		_Password = Password;
	}
	string getPassword()
	{
		return _Password;
	}
	__declspec(property(get = getPassword, put = setPassword))string Password;

	void setPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	int getPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = getPermissions, put = setPermissions))int Permissions;

	static clsUser Find(string Username)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.Username == Username)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string Username, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.Username == Username && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	enum enSaveResults { svFailedEmptyObject = 0 , svSucceeded =1, svFailedUserExists = 2};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
				return enSaveResults::svFailedEmptyObject;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::AddNewMode:
		{
			if (clsUser::DoesUserExist(_Username))
			{
				return enSaveResults::svFailedUserExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;
		}
		}
	}

	static bool DoesUserExist(string Username)
	{
		clsUser User = clsUser::Find(Username);
		return (!User.IsEmpty());
	}

	bool Delete()
	{
		vector <clsUser> vUsers;

		vUsers = _LoadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.Username == _Username)
			{
				User._MarkedForDeletion = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static clsUser GetAddNewUserObject(string Username)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", Username, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	void RegisterLogin()
	{
		string stDataLine = _PrepareLoginRecord();

		fstream MyFile;
		MyFile.open("Registrations.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vRegistrations;

		fstream MyFile;
		MyFile.open("Registrations.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vRegistrations.push_back(_ConvertRegisterLineToRecord(Line));
			}
			MyFile.close();
		}

		return vRegistrations;
	}

	

};


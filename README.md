# OOP Bank Management System

A console-based bank management system built with C++ using Object-Oriented Programming. The system includes client management, user access control with bitwise permissions, financial transactions, transfer logging, login registration tracking, and a currency exchange module.

## Architecture
The project follows a clean OOP structure separating business logic from UI:
- **Business logic**: `clsBankClient`, `clsUser`, `clsCurrency`, `clsPerson`
- **Screen classes**: one class per screen, all inheriting from `clsScreen`
- **Utilities**: `clsInputValidate`, `clsString`, `clsDate`

## Login
- Authenticate with username and password before accessing any feature
- Locked after 3 failed login attempts
- Every successful login is recorded with timestamp in `LoginRegister.txt`

## Main Menu
- **Show Client List**: displays all clients with account details
- **Add New Client**: validates unique account number, saves to `Clients.txt`
- **Delete Client**: shows client card and asks for confirmation before deleting
- **Update Client Info**: edit all fields except account number
- **Find Client**: search by account number
- **Transactions**: opens transactions submenu
- **Manage Users**: opens user management submenu
- **Login Register**: view full login history with timestamps
- **Currency Exchange**: opens currency exchange submenu
- **Logout**

## Transactions Menu
- **Deposit**: add amount to client balance
- **Withdraw**: deduct amount with balance validation
- **Total Balances**: display all clients with total balance sum
- **Transfer**: transfer amount between two clients, logged to `TransferLog.txt`

## Manage Users Menu
- **List Users**: display all system users with permissions
- **Add New User**: set username, password, and granular permissions
- **Delete User**: confirmation required, Admin cannot be deleted
- **Update User**: edit user info and permissions
- **Find User**: search by username

## User Permissions
Permissions are assigned per user using **bitwise OR**, allowing fine-grained access control over each feature individually. Full access can be granted with a single flag (`-1`).

Available permissions:
- Show Client List, Add Client, Delete Client, Update Client, Find Client
- Transactions, Manage Users, Login Register, Currency Exchange

## Currency Exchange Menu
- **List Currencies**: display all currencies with country, code, name, and rate
- **Find Currency**: search by currency code or country name
- **Update Rate**: update exchange rate for a currency
- **Currency Calculator**: convert any amount between two currencies

## File Storage
All data is stored in plain text files using `#//# ` as a field separator:

| File | Contents |
|---|---|
| `Clients.txt` | Bank client records |
| `Users.txt` | System user records |
| `Currencies.txt` | Currency data and rates |
| `TransferLog.txt` | Transfer transaction history |
| `LoginRegister.txt` | Login history with timestamps |

## Dependencies
Uses personal utility libraries:
- `clsString.h`: string manipulation utilities
- `clsDate.h`: date and time utilities
- `clsInputValidate.h`: Input validation
- 
## How to Run
1. Place all `.h` files and the utility libraries in the same directory
2. Compile:
3. Run, data files are created automatically on first use

## Technologies
C++, OOP, Inheritance, File Handling (fstream), Bitwise Operations, Vectors, Static Classes

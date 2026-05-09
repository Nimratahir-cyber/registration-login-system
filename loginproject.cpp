#include<iostream>
#include<windows.h>
#include<vector>
#include<fstream>
#include<sstream>
#include<conio.h>
using namespace std;

// ---------------- Utility ----------------
string trim(string s)
{
    int start = 0, end = s.length() - 1;

    while (start <= end && s[start] == ' ')
        start++;

    while (end >= start && s[end] == ' ')
        end--;

    return s.substr(start, end - start + 1);
}

// ---------------- Bank Class ----------------
class BankAccount {
public:
    string name;
    int balance = 0;

    void deposit(int money) {
        balance += money;
    }

    bool withdraw(int money) {
        if (money <= balance) {
            balance -= money;
            return true;
        }
        return false;
    }

    void showBalance() {
        cout << "Your balance: Rs. " << balance << endl;
    }
};

// ---------------- Login Class ----------------
class Login {
private:
    string username, password;

public:
    void set(string uname, string pword) {
        username = uname;
        password = pword;
    }

    string get() {
        return username + " | " + password;
    }
};

// ---------------- Global Storage ----------------
vector<BankAccount> accounts;
BankAccount* currentUser = nullptr;

// ---------------- Bank System ----------------
void bankMenu() {
    int choice;

    do {

        cout << "\n------ Bank Menu ------\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Balance\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int money;
            cout << "Enter amount: ";
            cin >> money;
            currentUser->deposit(money);
            cout<<"money deposited successfully!"<<endl;
            getch();
            Sleep(1000);
            system("cls");
            break;
        }
        case 2: {
            int money;
            cout << "Enter amount: ";
            cin >> money;
            if (currentUser->withdraw(money))
                cout << "Withdraw successful\n";
            else
                cout << "Insufficient balance\n";
                getch();
                Sleep(1000);
                system("cls");
            break;
        }
        case 3:
            currentUser->showBalance();
            getch();
            Sleep(1000);
            system("cls");
            break;
        case 4:
            cout << "Logging out";
            for(int i=0;i<3;i++){
                cout<<".";
                Sleep(500);
            }
            cout<<endl;
            system("cls");
            currentUser=nullptr;
            break;
        default:
            cout << "Invalid choice\n";
        }

    } while (choice != 4);
}

// ---------------- Registration ----------------
void registerUser() {
    system("cls");

    string uname, pword;

    cout << "Enter username: ";
    getline(cin, uname);

    do {
        cout << "Enter password (min 8 chars): ";
        getline(cin, pword);
    } while (pword.length() < 8);

    Login l;
    l.set(uname, pword);

    ofstream file("users.txt", ios::app);
    file << l.get() << endl;
    file.close();

    // create bank account
    BankAccount acc;
    acc.name = uname;
    accounts.push_back(acc);

    cout << "Registered successfully!\n";
    Sleep(1500);
    system("cls");
}

// ---------------- Login ----------------
void loginUser() {
    system("cls");

    string uname, pword;
    cout << "Enter username: ";
    getline(cin, uname);
    cout << "Enter password: ";
    getline(cin, pword);

    ifstream file("users.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string u, p;

        getline(ss, u, '|');
        getline(ss, p, '|');

        u = trim(u);
        p = trim(p);

        if (u == uname && p == pword) {
            found = true;

            cout << "Logging in";
            for (int i = 0; i < 3; i++) {
                cout << ".";
                Sleep(500);
            }
            cout<<endl;
            system("cls");

            // find user account
            for (auto &acc : accounts) {
                if (acc.name == uname) {
                    currentUser = &acc;
                    bankMenu();
                    return;
                }
            }
        }
    }

    if (!found) {
        cout << "Invalid credentials\n";
        getch();
        Sleep(1000);
        system("cls");
    }

    file.close();
}

// ---------------- Main ----------------
int main() {
    int choice;

    do {
        cout << "\n------ Main Menu ------\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid input\n";
        }

    } while (choice != 3);

    return 0;
}

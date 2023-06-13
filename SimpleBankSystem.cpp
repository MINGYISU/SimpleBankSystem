// Author: Mingyi Su
// This program simulates a bank system from a client's 

#include <iostream>
#include <string>

using namespace std;

const int SUCCESS = 1;
const int NOT_FOUND = -1;
const int FAILURE = -2;

class Account {
    string m_firstname{};
    string m_lastname{};
    string m_address{};
    string m_password{};
    int m_SIN;
    float m_deposit;

public:
    Account(int sin = 0,float dep = 0.0): m_SIN{sin}, m_deposit{dep} {}; //initializing

    friend istream& operator>> (istream& in, Account& e) {
            system("clear");
            cout << "Enter the first name: ";
            in >> e.m_firstname;
            cout << "Enter the last name: ";
            in >> e.m_lastname;
            cout << "Enter the address: ";
            getchar();
            getline(in, e.m_address);
            cout << "Enter the social insurance number: ";
            in >> e.m_SIN;
            cout << "Enter the amount you want to deposit: ";
            in >> e.m_deposit; //getting the data
            cout << "Set up a password for your account(Do NOT include WHITESPACE!): ";
            in >> e.m_password;
        return in;
    }

    friend ostream& operator<<(ostream& out, Account& e) {
        out << "Account Information: ";
        out << endl << "Name: " << e.m_firstname << " " << e.m_lastname;
        out << endl << "Password: " << e.m_password;
        out << endl << "Address: " << e.m_address;
        out << endl << "Social Insurance Number: " << e.m_SIN;
        out << endl << "Balance: " << e.m_deposit << endl; //output the data
        return out;
    }

    string returnFN() {
        return m_firstname;
    }

    string returnPW() {
        return m_password;
    }

    int returnSIN() {
        return m_SIN;
    }

    float returnBal() {
        return m_deposit;
    }

    void resetPW(string new_pw) {
        m_password = new_pw;
    }

    void depositBal(int amt) {
        if (amt > 0) {
            m_deposit += amt;
        }
    }

    int withBal(int amt) {
        if (amt <= 0 || m_deposit < amt) {
            return FAILURE;
        } else {
            m_deposit -= amt;
            return SUCCESS;
        }
    }

    friend int search(Account* e, int id, int s);
};

// search(e, id, s) returns the position(int) of the 
//      account in e that matches the id
int search(Account* e, int id, int s) {
    for (int i = 0; i < s; i++) {
        if (id == (e + i)->m_SIN){
            return i;
        }
    }
    return NOT_FOUND;
}

// buffer() pauses the program and allows the user to view 
//      the info and then continue whenever they want
void buffer() {
    cout << endl << "Press ENTER to Continue: ";
    cin.get();
    cin.ignore();
}

int main() {
    int wanted, choice{}, login{}, size{}, capacity{1}, amount;
    string input, cmd, pw;
    Account* acc{new Account[capacity]{}};
    system("clear"); // change to system("cls"); in Windows
    while (true) {
        system("clear"); // change to system("cls"); in Windows
        cout << "1-Create a NEW Account" << endl;
        cout << "2-Log In to Your Account" << endl;
        cout << "3-Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 3) {
            break;
        }

        if (choice == 1) {
            if (size == capacity - 1) {
                capacity *= 2;
                Account* new_arr = new Account[capacity]{};
                for (int i = 0; i < size; ++i) {
                    new_arr[i] = acc[i];
                }
                delete[] acc;
                acc = new_arr;
            }
            cin >> acc[size]; //entering the elements
            size++;
            system("clear");
            cout << "Account Registered Successfully! "<< "Welcome, " << acc[size - 1].returnFN() << "! Thank you for choosing us!" << endl;
            buffer();
        } else if (choice == 2) {
            system("clear"); // change to system("cls"); in Windows
            cout<<"Enter the ID(SIN) you want to find: ";   // To simplify the problem, use SIN as ID, assuming that SIN is unique
            cin >> wanted;
            login = search(acc,wanted,size); // Find the account
            if (login == NOT_FOUND) {
                cout << "Account Not Found!";
                buffer();
                continue;
            }
            cout << endl << "Please Enter the Password(Do NOT include WHITESPACE!): ";
            cin >> input;
            if (input != acc[login].returnPW()) {
                cout << "Wrong Password!" << endl;
                buffer();
                continue;
            } else {
                while (true) {
                    system("clear");
                    cout << acc[login];
                    cout << "Enter the options below to manage your account" << endl;
                    cout << "RESET: Reset Your Password" << endl;
                    cout << "DEPOSIT: Make a Deposit" << endl;
                    cout << "WITHDRAW: Make a Withdraw" << endl;
                    cout << "CLOSE: Close Your Account" << endl;
                    cout << "QUIT: Quit" << endl;
                    cout << "Select an option: ";
                    cin >> cmd;
                    if (cmd == "RESET") {
                        cout << "Enter your new Password(Do NOT Include WHITESPACE!): ";
                        cin >> pw;
                        acc[login].resetPW(pw);
                        cout << "Password Updated!" << endl;
                        buffer();
                    } else if (cmd == "DEPOSIT") {
                        cout << "Enter the amount you want to deposit: ";
                        cin >> amount;
                        acc[login].depositBal(amount);
                        cout << "Deposit Alert: A Deposit of " << amount << " has been made from your accout " << acc[login].returnSIN() << endl;
                        buffer();
                    } else if (cmd == "WITHDRAW") {
                        cout << "Enter the amount you want to withdraw: ";
                        cin >> amount;
                        if (acc[login].withBal(amount) == FAILURE) {
                            cout << "NOT SUFFICIENT FUNDS!";
                            buffer();
                            continue;
                        }
                        cout << "Withdraw Alert: A withdraw of " << amount << " has been made from your account " << acc[login].returnSIN() << endl;
                        buffer();
                    } else if (cmd == "CLOSE") {
                        for (int i = login; i < size - 1; ++i) {
                            acc[i] = acc[i + 1];
                        }
                        size--;
                        cout << "Account Closure Confirmed" << endl;
                        buffer();
                        break;
                    } else if (cmd == "QUIT") {
                        break;
                    } else {
                        cout << "Unkown Command!";
                        buffer();
                        continue;
                    }
                }
            }
        } else {
            continue;
        }
    }
}

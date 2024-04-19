#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to represent a bank account
struct BankAccount {
    string accountNumber;
    string accountHolderName;
    double balance;
};

// Function to create a new bank account
void createAccount(vector<BankAccount>& accounts) {
    BankAccount newAccount;
    cout << "Enter account number: ";
    cin >> newAccount.accountNumber;
    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, newAccount.accountHolderName);
    newAccount.balance = 0.0;
    accounts.push_back(newAccount);
    cout << "Account created successfully." << endl;
}

// Function to make a deposit into a bank account
void makeDeposit(vector<BankAccount>& accounts) {
    string accountNumber;
    double amount;
    cout << "Enter account number: ";
    cin >> accountNumber;

    for (BankAccount& account : accounts) {
        if (account.accountNumber == accountNumber) {
            cout << "Enter deposit amount: ";
            cin >> amount;
            if (amount > 0) {
                account.balance += amount;
                cout << "Deposit successful. Current balance: " << account.balance << endl;
            } else {
                cout << "Invalid deposit amount. Please enter a positive value." << endl;
            }
            return;
        }
    }
    cout << "Account not found." << endl;
}

// Function to make a withdrawal from a bank account
void makeWithdrawal(vector<BankAccount>& accounts) {
    string accountNumber;
    double amount;
    cout << "Enter account number: ";
    cin >> accountNumber;

    for (BankAccount& account : accounts) {
        if (account.accountNumber == accountNumber) {
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            if (amount > 0 && amount <= account.balance) {
                account.balance -= amount;
                cout << "Withdrawal successful. Current balance: " << account.balance << endl;
            } else {
                cout << "Invalid withdrawal amount or insufficient balance." << endl;
            }
            return;
        }
    }
    cout << "Account not found." << endl;
}

// Function to check balance of a bank account
void checkBalance(const vector<BankAccount>& accounts) {
    string accountNumber;
    cout << "Enter account number: ";
    cin >> accountNumber;

    for (const BankAccount& account : accounts) {
        if (account.accountNumber == accountNumber) {
            cout << "Account Holder Name: " << account.accountHolderName << endl;
            cout << "Account Balance: " << account.balance << endl;
            return;
        }
    }
    cout << "Account not found." << endl;
}

int main() {
    vector<BankAccount> accounts;
    char choice;

    do {
        cout << "\nBank Account Management System" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Make Deposit" << endl;
        cout << "3. Make Withdrawal" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case '1':
                createAccount(accounts);
                break;
            case '2':
                makeDeposit(accounts);
                break;
            case '3':
                makeWithdrawal(accounts);
                break;
            case '4':
                checkBalance(accounts);
                break;
            case '5':
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }
    } while (choice != '5');

    return 0;
}

#include <iostream>

using namespace std;

class ATM {
private:
    double balance;

public:
    ATM() {
        balance = 0.0;
    }

    void displayMenu() {
        cout << "====================" << endl;
        cout << "ATM MENU" << endl;
        cout << "====================" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Exit" << endl;
    }

    void checkBalance() {
        cout << "Your balance is: Rs." << balance << endl;
    }

    void deposit() {
        double amount;
        cout << "Enter the amount to deposit: Rs.";
        cin >> amount;
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful!" << endl;
        } else {
            cout << "Invalid amount. Please enter a positive amount." << endl;
        }
    }

    void withdraw() {
        double amount;
        cout << "Enter the amount to withdraw: Rs.";
        cin >> amount;
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful!" << endl;
        } else {
            cout << "Invalid amount or insufficient balance." << endl;
        }
    }

    void run() {
        int choice;
        do {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    checkBalance();
                    break;
                case 2:
                    deposit();
                    break;
                case 3:
                    withdraw();
                    break;
                case 4:
                    cout << "Thank you for using the ATM. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 4);
    }
};

int main() {
    ATM atm;
    atm.run();
    return 0;
}

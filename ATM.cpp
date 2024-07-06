#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>  // Include stringstream for number-to-string conversion

using namespace std;

const int CONSOLE_WIDTH = 80; // Adjust this according to your console width

void printCentered(const string &text) {
    int padding = (CONSOLE_WIDTH - text.length()) / 2;
    cout << setw(padding) << "" << text << endl;
}

// Function to convert number to string
string numberToString(double number) {
    ostringstream oss;
    oss << number;
    return oss.str();
}

class ATM {
private:
    double balance;

public:
    ATM() : balance(0.0) {}

    void displayMenu() const {
        printCentered("====================");
        printCentered("ATM MENU");
        printCentered("====================");
        printCentered("1. Check Balance");
        printCentered("2. Deposit");
        printCentered("3. Withdraw");
        printCentered("4. Exit");
    }

    void checkBalance() const {
        printCentered("Your balance is: Rs." + numberToString(balance));
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            printCentered("Deposit of Rs." + numberToString(amount) + " successful!");
        } else {
            printCentered("Invalid amount. Please enter a positive amount.");
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            printCentered("Withdrawal of Rs." + numberToString(amount) + " successful!");
        } else {
            printCentered("Invalid amount or insufficient balance.");
        }
    }

    void run() {
        int choice;
        do {
            displayMenu();
            printCentered("Enter your choice: ");
            cin >> choice;
            switch (choice) {
                case 1:
                    checkBalance();
                    break;
                case 2: {
                    double amount;
                    printCentered("Enter the amount to deposit: Rs.");
                    cin >> amount;
                    deposit(amount);
                    break;
                }
                case 3: {
                    double amount;
                    printCentered("Enter the amount to withdraw: Rs.");
                    cin >> amount;
                    withdraw(amount);
                    break;
                }
                case 4:
                    printCentered("Thank you for using the ATM. Goodbye!");
                    break;
                default:
                    printCentered("Invalid choice. Please try again.");
            }
        } while (choice != 4);
    }
};

int main() {
    ATM atm;
    atm.run();
    return 0;
}


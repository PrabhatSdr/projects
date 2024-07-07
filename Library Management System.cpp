#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Person {
protected:
    string name;
    int id;
public:
    Person(string name, int id) : name(name), id(id) {}
    virtual void showDetails() = 0; // Pure virtual function
};

class Book {
public:
    static int bookCounter;
    int bookId;
    string title;

    Book(string title) : title(title) {
        bookId = ++bookCounter;
    }

    void showDetails() {
        cout << "Book ID: " << bookId << ", Title: " << title << endl;
    }
};

int Book::bookCounter = 0;

class Student : public Person {
public:
    Student(string name, int id) : Person(name, id) {}

    void renewBook(int days) {
        if (days > 20) {
            cout << "You have to pay a fine as you renewed the book after " << days << " days." << endl;
        } else {
            cout << "Book renewed successfully." << endl;
        }
    }

    void purchaseBook(string title, vector<Book>& books) {
        Book newBook(title);
        books.push_back(newBook);
        cout << "Book purchased successfully. Book ID: " << newBook.bookId << endl;
    }

    void showDetails() override {
        cout << "Student Name: " << name << ", ID: " << id << endl;
    }
};

class Employee : public Person {
public:
    Employee(string name, int id) : Person(name, id) {}

    void checkShift() {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        int hour = ltm->tm_hour;
        int minute = ltm->tm_min;

        cout << "Current time is: " << (hour < 10 ? "0" : "") << hour << ":"
             << (minute < 10 ? "0" : "") << minute << endl;

        if (hour >= 9 && hour < 17) {
            cout << "You are within your shift time." << endl;
        } else {
            cout << "You are outside of your shift time." << endl;
        }
    }

    void recordVisits(int studentCount) {
        cout << "Number of students visited today: " << studentCount << endl;
    }

    void showDetails() override {
        cout << "Employee Name: " << name << ", ID: " << id << endl;
    }
};

void displayMenu() {
    cout << "Select the type of user: " << endl;
    cout << "1. Student" << endl;
    cout << "2. Employee" << endl;
}

void studentMenu() {
    cout << "Select the work: " << endl;
    cout << "1. Renew the book" << endl;
    cout << "2. Purchase the book" << endl;
    cout << "3. Others" << endl;
}

void employeeMenu() {
    cout << "Select the work: " << endl;
    cout << "1. Check shift timings" << endl;
    cout << "2. Record student visits" << endl;
    cout << "3. Others" << endl;
}

int main() {
    vector<Book> books;
    vector<Student> students;
    vector<Employee> employees;

    int choice, work, days, studentCount = 0;
    string name, title;
    int id;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: // Student
                cout << "Enter Student Name: ";
                cin.ignore(); // Ignore the newline character from previous input
                getline(cin, name);
                cout << "Enter Student ID: ";
                cin >> id;
                {
                    Student student(name, id);
                    student.showDetails();
                    students.push_back(student);

                    studentMenu();
                    cin >> work;

                    switch (work) {
                        case 1: // Renew the book
                            cout << "Enter the number of days since the book was borrowed: ";
                            cin >> days;
                            student.renewBook(days);
                            break;
                        case 2: // Purchase the book
                            cout << "Enter the title of the book: ";
                            cin.ignore(); // Ignore the newline character from previous input
                            getline(cin, title);
                            student.purchaseBook(title, books);
                            break;
                        case 3: // Others
                            cout << "Performing other tasks for student." << endl;
                            break;
                    }
                    studentCount++; // Increment the student visit counter
                }
                break;

            case 2: // Employee
                cout << "Enter Employee Name: ";
                cin.ignore(); // Ignore the newline character from previous input
                getline(cin, name);
                cout << "Enter Employee ID: ";
                cin >> id;
                {
                    Employee employee(name, id);
                    employee.showDetails();
                    employees.push_back(employee);

                    employeeMenu();
                    cin >> work;

                    switch (work) {
                        case 1: // Check shift timings
                            employee.checkShift();
                            break;
                        case 2: // Record student visits
                            employee.recordVisits(studentCount);
                            break;
                        case 3: // Others
                            cout << "Performing other tasks for employee." << endl;
                            break;
                    }
                }
                break;

            default:
                cout << "Invalid choice! Exiting..." << endl;
                return 0;
        }
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <set>

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

    void renewBooks(vector<pair<string, string> >& borrowedBooks) {
        for (size_t i = 0; i < borrowedBooks.size(); ++i) {
            const string& title = borrowedBooks[i].first;
            const string& borrowedDate = borrowedBooks[i].second;

            // Parse the date string (YYYY-MM-DD)
            int year, month, day;
            sscanf(borrowedDate.c_str(), "%d-%d-%d", &year, &month, &day);

            // Create a tm structure for the borrowed date
            tm borrowed = {};
            borrowed.tm_year = year - 1900; // Year since 1900
            borrowed.tm_mon = month - 1;    // Months are 0-based
            borrowed.tm_mday = day;

            time_t borrowedTime = mktime(&borrowed);

            // Get the current time
            time_t now = time(0);

            // Check if the borrowed date is in the future
            if (borrowedTime > now) {
                cout << "Error: The date \"" << borrowedDate << "\" is in the future and is invalid." << endl;
                continue;
            }

            // Calculate the difference in days
            double seconds = difftime(now, borrowedTime);
            int days = seconds / (60 * 60 * 24);

            if (days > 20) {
                cout << "You have to pay a fine for the book \"" << title << "\" as you renewed it after " << days << " days." << endl;
            } else {
                cout << "Book \"" << title << "\" renewed successfully." << endl;
            }
        }
    }

    void purchaseBook(vector<string>& titles, vector<Book>& books, map<string, int>& bookStock) {
        for (size_t i = 0; i < titles.size(); ++i) {
            string title = titles[i];
            if (bookStock[title] >= 5) {
                cout << "The book \"" << title << "\" is out of stock." << endl;
            } else {
                Book newBook(title);
                books.push_back(newBook);
                bookStock[title]++;
                cout << "Book purchased successfully. Book ID: " << newBook.bookId << endl;
            }
        }
    }

    void showDetails() {
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

    void showDetails() {
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
    cout << "1. Renew the book(s)" << endl;
    cout << "2. Purchase the book" << endl;
    cout << "3. Others" << endl;
}

void employeeMenu() {
    cout << "Select the work: " << endl;
    cout << "1. Check shift timings" << endl;
    cout << "2. Record student visits" << endl;
    cout << "3. Others" << endl;
}

bool askForMoreTasks() {
    char choice;
    cout << "Do you want to perform another task? (y/n): ";
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

int main() {
    vector<Book> books;
    vector<Student> students;
    vector<Employee> employees;
    map<string, int> bookStock; // To keep track of the number of times a book is purchased
    set<int> usedIds; // To keep track of used IDs

    int choice, work, studentCount = 0;
    string name, title, borrowedDate;
    int id;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Ignore the newline character from previous input

        switch (choice) {
            case 1: // Student
                cout << "Enter Student Name: ";
                getline(cin, name);
                cout << "Enter Student ID: ";
                cin >> id;
                cin.ignore(); // Ignore the newline character from previous input

                if (usedIds.find(id) != usedIds.end()) {
                    cout << "Error: ID already in use. Please enter your ID." << endl;
                    break;
                }

                usedIds.insert(id);

                {
                    Student student(name, id);
                    student.showDetails();
                    students.push_back(student);

                    do {
                        studentMenu();
                        cin >> work;
                        cin.ignore(); // Ignore the newline character from previous input

                        switch (work) {
                            case 1: { // Renew the book(s)
                                int numBooks;
                                cout << "Enter the number of books to renew: ";
                                cin >> numBooks;
                                cin.ignore(); // Ignore the newline character from previous input
                                vector<pair<string, string> > borrowedBooks;

                                for (int i = 0; i < numBooks; ++i) {
                                    cout << "Enter the title of book " << (i + 1) << ": ";
                                    getline(cin, title);
                                    cout << "Enter the date when the book was borrowed (YYYY-MM-DD): ";
                                    getline(cin, borrowedDate);
                                    borrowedBooks.push_back(make_pair(title, borrowedDate));
                                }

                                student.renewBooks(borrowedBooks);
                                break;
                            }
                            case 2: { // Purchase the book
                                int numBooks;
                                cout << "Enter the number of books to purchase: ";
                                cin >> numBooks;
                                cin.ignore(); // Ignore the newline character from previous input
                                vector<string> titles;
                                
                                for (int i = 0; i < numBooks; ++i) {
                                    cout << "Enter the title of book " << (i + 1) << ": ";
                                    getline(cin, title);
                                    titles.push_back(title);
                                }

                                student.purchaseBook(titles, books, bookStock);
                                break;
                            }
                            case 3: // Others
                                cout << "Performing other tasks for student." << endl;
                                break;
                        }
                    } while (askForMoreTasks());

                    studentCount++; // Increment the student visit counter
                }
                break;

            case 2: // Employee
                cout << "Enter Employee Name: ";
                getline(cin, name);
                cout << "Enter Employee ID: ";
                cin >> id;
                cin.ignore(); // Ignore the newline character from previous input

                if (usedIds.find(id) != usedIds.end()) {
                    cout << "Error: ID already in use. Please enter your ID." << endl;
                    break;
                }

                usedIds.insert(id);

                {
                    Employee employee(name, id);
                    employee.showDetails();
                    employees.push_back(employee);

                    do {
                        employeeMenu();
                        cin >> work;
                        cin.ignore(); // Ignore the newline character from previous input

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
                    } while (askForMoreTasks());
                }
                break;

            default:
                cout << "Invalid choice! Exiting..." << endl;
                return 0;
        }
    }

    return 0;
}


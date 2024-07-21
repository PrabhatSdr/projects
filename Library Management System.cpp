#include <iostream>
#include <vector>
#include <string>
#include <ctime>
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
                cout << "You have to return the book \"" << title << "\" as it has been more than 20 days since it was borrowed." << endl;
            } else {
                cout << "You have " << 20 - days << " days left to return the book \"" << title << "\"." << endl;
            }
        }
    }

    void returnBooks(vector<pair<string, string> >& borrowedBooks) {
        string title, borrowedDate;
        cout << "Enter the title of the book to return: ";
        getline(cin, title);
        cout << "Enter the borrowed date (YYYY-MM-DD): ";
        getline(cin, borrowedDate);

        for (vector<pair<string, string> >::iterator it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (it->first == title && it->second == borrowedDate) {
                borrowedBooks.erase(it);
                cout << "The book \"" << title << "\" borrowed on " << borrowedDate << " has been returned." << endl;
                return;
            }
        }
        cout << "Error: Book with title \"" << title << "\" and borrowed date \"" << borrowedDate << "\" not found." << endl;
    }

    void purchaseBooks(vector<Book>& books) {
        string title;
        cout << "Enter the title of the book to purchase: ";
        getline(cin, title);

        books.push_back(Book(title));
        cout << "Book \"" << title << "\" has been purchased and added to the library." << endl;
    }

    void showDetails() {
        cout << "Student Name: " << name << ", ID: " << id << endl;
    }
};

class Employee : public Person {
    string shift;
public:
    Employee(string name, int id, string shift) : Person(name, id), shift(shift) {}

    void checkShift() {
        // Function logic
    }

    void recordVisits(int studentCount) {
        // Function logic
    }

    void showDetails() {
        cout << "Employee Name: " << name << ", ID: " << id << ", Shift: " << shift << endl;
    }
};

void studentMenu() {
    cout << "1. Renew Books\n2. Return Books\n3. Purchase Books\n4. Exit\nEnter your choice: ";
}

void employeeMenu() {
    cout << "1. Check shift timings\n2. Record student visits\n3. Exit\nEnter your choice: ";
}

bool askForMoreTasks() {
    char choice;
    cout << "Do you want to perform more tasks? (y/n): ";
    cin >> choice;
    cin.ignore(); // Ignore the newline character from previous input
    return (choice == 'y' || choice == 'Y');
}

int main() {
    vector<Student> students;
    vector<Employee> employees;
    vector<Book> books;
    set<int> usedIds;
    int studentCount = 0;

    while (true) {
        int choice;
        cout << "1. Student\n2. Employee\n3. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character from previous input

        switch (choice) {
            case 1: {
                string name;
                int id;
                cout << "Enter your name: ";
                getline(cin, name);
                cout << "Enter your ID: ";
                cin >> id;
                cin.ignore(); // Ignore the newline character from previous input

                if (usedIds.find(id) != usedIds.end()) {
                    cout << "Error: ID already in use. Please enter your ID." << endl;
                    break;
                }

                usedIds.insert(id);

                Student student(name, id);
                student.showDetails();
                students.push_back(student);

                vector<pair<string, string> > borrowedBooks;
                int task;
                do {
                    studentMenu();
                    cin >> task;
                    cin.ignore(); // Ignore the newline character from previous input

                    switch (task) {
                        case 1:
                            student.renewBooks(borrowedBooks);
                            break;
                        case 2:
                            student.returnBooks(borrowedBooks);
                            break;
                        case 3:
                            student.purchaseBooks(books);
                            break;
                        case 4:
                            cout << "Exiting student section." << endl;
                            break;
                        default:
                            cout << "Invalid choice! Please enter a valid option." << endl;
                    }
                } while (task != 4);
                break;
            }
            case 2: {
                string name;
                int id;
                cout << "Enter your name: ";
                getline(cin, name);
                cout << "Enter your ID: ";
                cin >> id;
                cin.ignore(); // Ignore the newline character from previous input

                if (usedIds.find(id) != usedIds.end()) {
                    cout << "Error: ID already in use. Please enter your ID." << endl;
                    break;
                }

                usedIds.insert(id);

                cout << "Enter your shift (day/night): ";
                string shift;
                getline(cin, shift);

                // Get the current time
                time_t now = time(0);
                tm *ltm = localtime(&now);
                int hour = ltm->tm_hour;

                if ((shift == "day" && (hour < 8 || hour >= 18)) || (shift == "night" && (hour >= 8 && hour < 18))) {
                    cout << "Error: The shift \"" << shift << "\" is invalid according to the current time." << endl;
                    usedIds.erase(id); // Remove the ID from used IDs as the employee is not valid
                    break;
                }

                Employee employee(name, id, shift);
                employee.showDetails();
                employees.push_back(employee);

                int work;
                do {
                    employeeMenu();
                    cin >> work;
                    cin.ignore(); // Ignore the newline character from previous input

                    switch (work) {
                        case 1:
                            employee.checkShift();
                            break;
                        case 2:
                            employee.recordVisits(studentCount);
                            break;
                        case 3:
                            cout << "Exiting employee section." << endl;
                            break;
                        default:
                            cout << "Invalid choice! Please enter a valid option." << endl;
                    }
                } while (work != 3 && askForMoreTasks());
                break;
            }
            case 3:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice! Exiting..." << endl;
                return 0;
        }
    }

    return 0;
}


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class TaskList {
private:
    vector<string> tasks;
    string filename;

public:
    // Constructor to initialize with filename and load tasks from file
    TaskList(const string &filename) : filename(filename) {
        loadTasks(); // Load tasks from file
    }

    // Function to add a new task to the list
    void addTask(const string &task) {
        tasks.push_back(task);
    }

    // Function to display all tasks in the list
    void displayTasks() const {
        cout << "To-Do List:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i] << endl;
        }
    }

    // Function to save the current list of tasks to file
    void saveTasks() const {
        ofstream outputFile(filename.c_str()); // Open file for writing (C++98 compatible)
        if (!outputFile) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        // Write each task to file
        for (vector<string>::const_iterator it = tasks.begin(); it != tasks.end(); ++it) {
            outputFile << *it << endl;
        }
        outputFile.close(); // Close file
    }

    // Main function to run the task list application
    void run() {
        char choice;
        do {
            cout << "A - Add a task" << endl;
            cout << "V - View tasks" << endl;
            cout << "Q - Quit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 'A':
                case 'a': {
                    string task;
                    cout << "Enter a task: ";
                    cin.ignore(); // Clear input buffer
                    getline(cin, task); // Get task from user
                    addTask(task); // Add task to list
                    break;
                }
                case 'V':
                case 'v':
                    displayTasks(); // Display all tasks in the list
                    break;
            }
        } while (choice != 'Q' && choice != 'q'); // Repeat until user quits

        saveTasks(); // Save tasks to file when program exits
    }

private:
    // Function to load tasks from file
    void loadTasks() {
        ifstream inputFile(filename.c_str()); // Open file for reading (C++98 compatible)
        string task;
        while (getline(inputFile, task)) {
            tasks.push_back(task); // Add task to vector
        }
        inputFile.close(); // Close file
    }
};

// Main function to start the task list application
int main() {
    TaskList taskList("tasks.txt"); // Create TaskList object with filename "tasks.txt"
    taskList.run(); // Start the task list application

    return 0; // Exit program
}


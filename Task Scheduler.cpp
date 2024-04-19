#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

// Structure to represent a task
struct Task {
    string title;
    string description;
    time_t dueDate;
};

// Function to add a new task
void addTask(vector<Task>& tasks) {
    Task newTask;
    cout << "Enter task title: ";
    cin.ignore();
    getline(cin, newTask.title);
    cout << "Enter task description: ";
    getline(cin, newTask.description);

    // Get due date
    time_t now = time(nullptr);
    cout << "Enter due date (YYYY-MM-DD HH:MM): ";
    string dueDateStr;
    getline(cin, dueDateStr);

    // Convert string to time_t
    tm dueDateTm = {};
    strptime(dueDateStr.c_str(), "%Y-%m-%d %H:%M", &dueDateTm);
    newTask.dueDate = mktime(&dueDateTm);

    tasks.push_back(newTask);
    cout << "Task added successfully." << endl;
}

// Function to edit an existing task
void editTask(vector<Task>& tasks) {
    string titleToEdit;
    cout << "Enter the title of the task to edit: ";
    cin.ignore();
    getline(cin, titleToEdit);

    for (Task& task : tasks) {
        if (task.title == titleToEdit) {
            cout << "Enter new task description: ";
            getline(cin, task.description);

            // Get new due date
            cout << "Enter new due date (YYYY-MM-DD HH:MM): ";
            string dueDateStr;
            getline(cin, dueDateStr);
            tm dueDateTm = {};
            strptime(dueDateStr.c_str(), "%Y-%m-%d %H:%M", &dueDateTm);
            task.dueDate = mktime(&dueDateTm);

            cout << "Task edited successfully." << endl;
            return;
        }
    }
    cout << "Task not found." << endl;
}

// Function to delete a task
void deleteTask(vector<Task>& tasks) {
    string titleToDelete;
    cout << "Enter the title of the task to delete: ";
    cin.ignore();
    getline(cin, titleToDelete);

    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->title == titleToDelete) {
            tasks.erase(it);
            cout << "Task deleted successfully." << endl;
            return;
        }
    }
    cout << "Task not found." << endl;
}

// Function to display tasks for the day
void displayTasksForDay(const vector<Task>& tasks) {
    cout << "Tasks for the day:" << endl;
    time_t currentTime = time(nullptr);

    for (const Task& task : tasks) {
        if (task.dueDate >= currentTime && task.dueDate < currentTime + 86400) { // 86400 seconds = 1 day
            cout << "Title: " << task.title << endl;
            cout << "Description: " << task.description << endl;
            cout << "Due Date: " << put_time(localtime(&task.dueDate), "%Y-%m-%d %H:%M") << endl;
            cout << "-------------------" << endl;
        }
    }
}

int main() {
    vector<Task> tasks;
    char choice;

    do {
        cout << "\nTask Scheduler" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Edit Task" << endl;
        cout << "3. Delete Task" << endl;
        cout << "4. Display Tasks for the Day" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case '1':
                addTask(tasks);
                break;
            case '2':
                editTask(tasks);
                break;
            case '3':
                deleteTask(tasks);
                break;
            case '4':
                displayTasksForDay(tasks);
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

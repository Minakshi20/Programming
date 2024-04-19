#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structure to represent a task
struct Task {
    string name;
    string priority;
    bool completed;
};

// Function to add a task to the task list
void addTask(vector<Task>& taskList) {
    Task newTask;
    cout << "Enter task name: ";
    cin.ignore();
    getline(cin, newTask.name);
    cout << "Enter priority (high, medium, low): ";
    cin >> newTask.priority;
    newTask.completed = false;
    taskList.push_back(newTask);
    cout << "Task added successfully." << endl;
}

// Function to view tasks by priority
void viewTasksByPriority(const vector<Task>& taskList) {
    cout << "Tasks by Priority:" << endl;
    vector<Task> sortedTasks = taskList;
    sort(sortedTasks.begin(), sortedTasks.end(), [](const Task& a, const Task& b) {
        if (a.priority == "high" && b.priority != "high") return true;
        if (a.priority == "medium" && b.priority == "low") return true;
        return false;
    });

    for (const Task& task : sortedTasks) {
        cout << "Name: " << task.name << " | Priority: " << task.priority;
        if (task.completed) {
            cout << " (Completed)";
        }
        cout << endl;
    }
}

// Function to mark a task as completed
void markTaskCompleted(vector<Task>& taskList) {
    string taskName;
    cout << "Enter the name of the task to mark as completed: ";
    cin.ignore();
    getline(cin, taskName);

    for (Task& task : taskList) {
        if (task.name == taskName) {
            task.completed = true;
            cout << "Task marked as completed." << endl;
            return;
        }
    }
    cout << "Task not found." << endl;
}

int main() {
    vector<Task> taskList;
    char choice;

    do {
        cout << "\nTask List with Priority" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks by Priority" << endl;
        cout << "3. Mark Task as Completed" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case '1':
                addTask(taskList);
                break;
            case '2':
                viewTasksByPriority(taskList);
                break;
            case '3':
                markTaskCompleted(taskList);
                break;
            case '4':
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }
    } while (choice != '4');

    return 0;
}

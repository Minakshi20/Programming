#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure to store student information
struct Student {
    string name;
    vector<double> scores;
};

// Function to calculate the average score for a student
double calculateAverage(const vector<double>& scores) {
    if(scores.empty()) // Check if scores vector is empty
        return 0.0;
    
    double sum = 0.0;
    for(double score : scores) {
        sum += score;
    }
    return sum / scores.size();
}

int main() {
    vector<Student> students;
    char choice;

    do {
        Student student;
        cout << "Enter student name: ";
        cin >> student.name;

        cout << "Enter scores for " << student.name << " (enter -1 to finish): ";
        double score;
        while (true) {
            cin >> score;
            if (score == -1)
                break;
            student.scores.push_back(score);
        }

        students.push_back(student);

        cout << "Do you want to enter another student? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Display student information and average scores
    cout << "\nStudent Gradebook:" << endl;
    for(const Student& student : students) {
        cout << "\nStudent Name: " << student.name << endl;
        cout << "Scores:";
        for(double score : student.scores) {
            cout << " " << score;
        }
        cout << endl;
        cout << "Average Score: " << calculateAverage(student.scores) << endl;
    }

    return 0;
}

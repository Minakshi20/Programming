#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

// Structure to represent a quiz question
struct QuizQuestion {
    string question;
    vector<string> options;
    int correctOption;
};

// Function to generate a random quiz from a set of predefined questions
vector<QuizQuestion> generateQuiz() {
    vector<QuizQuestion> quiz;

    // Sample quiz questions (replace with your own questions)
    QuizQuestion question1 = {"What is the capital of France?",
                              {"A. London", "B. Paris", "C. Berlin", "D. Rome"},
                              1};
    QuizQuestion question2 = {"Which planet is known as the Red Planet?",
                              {"A. Mars", "B. Jupiter", "C. Venus", "D. Saturn"},
                              0};
    QuizQuestion question3 = {"What is the largest mammal?",
                              {"A. Elephant", "B. Blue Whale", "C. Giraffe", "D. Hippopotamus"},
                              1};

    quiz.push_back(question1);
    quiz.push_back(question2);
    quiz.push_back(question3);

    // Shuffle the quiz questions
    shuffle(quiz.begin(), quiz.end(), default_random_engine(time(nullptr)));

    return quiz;
}

// Function to take a quiz
void takeQuiz(const vector<QuizQuestion>& quiz) {
    int score = 0;

    cout << "Quiz Start!" << endl;
    cout << "--------------------------" << endl;

    // Display and answer each question
    for (size_t i = 0; i < quiz.size(); ++i) {
        const QuizQuestion& question = quiz[i];

        // Display question
        cout << i + 1 << ". " << question.question << endl;
        for (const string& option : question.options) {
            cout << "   " << option << endl;
        }

        // Get user's answer
        char userAnswer;
        cout << "Your answer (A/B/C/D): ";
        cin >> userAnswer;

        // Convert user's answer to option index
        int userOption = tolower(userAnswer) - 'a';

        // Check answer
        if (userOption == question.correctOption) {
            cout << "Correct!" << endl;
            ++score;
        } else {
            cout << "Incorrect. The correct answer is: " << question.options[question.correctOption] << endl;
        }

        cout << "--------------------------" << endl;
    }

    // Display final score
    cout << "Quiz Completed!" << endl;
    cout << "Your Score: " << score << "/" << quiz.size() << endl;
}

int main() {
    cout << "Welcome to the Quiz Generator!" << endl;

    // Generate a quiz
    vector<QuizQuestion> quiz = generateQuiz();

    // Take the generated quiz
    takeQuiz(quiz);

    return 0;
}

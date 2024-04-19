#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// List of predefined words
const vector<string> WORDS = {"hangman", "computer", "programming", "developer", "openai", "python"};

// Function to select a random word from the predefined word list
string getRandomWord() {
    srand(time(nullptr));
    return WORDS[rand() % WORDS.size()];
}

// Function to display the word with hidden letters
string hideWord(const string& word, const string& guessedLetters) {
    string hiddenWord;
    for (char letter : word) {
        if (guessedLetters.find(letter) != string::npos) {
            hiddenWord += letter;
        } else {
            hiddenWord += '_';
        }
    }
    return hiddenWord;
}

int main() {
    cout << "Welcome to Hangman!" << endl;

    string word = getRandomWord();
    string guessedLetters;
    int maxAttempts = 7;
    int attempts = 0;

    while (attempts < maxAttempts) {
        string hiddenWord = hideWord(word, guessedLetters);
        cout << "Word: " << hiddenWord << endl;
        cout << "Guessed Letters: " << guessedLetters << endl;

        if (hiddenWord == word) {
            cout << "Congratulations! You guessed the word: " << word << endl;
            break;
        }

        cout << "Enter a letter: ";
        char guess;
        cin >> guess;

        if (guessedLetters.find(guess) != string::npos) {
            cout << "You have already guessed that letter." << endl;
        } else {
            guessedLetters += guess;
            if (word.find(guess) == string::npos) {
                cout << "Incorrect guess." << endl;
                ++attempts;
            }
        }

        cout << "Attempts left: " << maxAttempts - attempts << endl;
    }

    if (attempts == maxAttempts) {
        cout << "Sorry, you ran out of attempts. The word was: " << word << endl;
    }

    return 0;
}

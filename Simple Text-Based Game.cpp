#include <iostream>
#include <string>

using namespace std;

// Function to present the player with a choice and return their decision
char presentChoice(const string& prompt, const string& option1, const string& option2) {
    char choice;
    cout << prompt << endl;
    cout << "1. " << option1 << endl;
    cout << "2. " << option2 << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;
    return choice;
}

// Function to display the ending message based on the player's final decision
void displayEnding(bool rescuedPrincess) {
    if (rescuedPrincess) {
        cout << "Congratulations! You have rescued the princess and saved the kingdom." << endl;
    } else {
        cout << "You have failed to rescue the princess. The kingdom is doomed." << endl;
    }
}

int main() {
    cout << "Welcome to the Adventure Game!" << endl;
    cout << "You are a brave knight on a quest to rescue the princess from the evil dragon." << endl;

    char choice1 = presentChoice("You arrive at a fork in the road. Which path will you take?",
                                 "Follow the path through the dark forest.",
                                 "Take the winding mountain trail.");

    char choice2;
    if (choice1 == '1') {
        choice2 = presentChoice("As you journey through the forest, you hear a strange noise. What will you do?",
                                "Investigate the noise.",
                                "Continue on your path.");
        if (choice2 == '1') {
            cout << "You encounter a group of bandits! They demand your gold." << endl;
            char choice3 = presentChoice("What will you do?",
                                         "Fight the bandits.",
                                         "Give them your gold.");
            if (choice3 == '1') {
                cout << "You defeat the bandits and continue your journey." << endl;
            } else {
                cout << "You give the bandits your gold and continue your journey." << endl;
            }
        }
    } else {
        choice2 = presentChoice("The mountain trail is treacherous. You hear rumblings ahead. What will you do?",
                                "Press forward.",
                                "Turn back.");
        if (choice2 == '1') {
            cout << "You reach the dragon's lair! The princess is inside." << endl;
            char choice3 = presentChoice("How will you confront the dragon?",
                                         "Challenge the dragon to a duel.",
                                         "Sneak past the dragon to rescue the princess.");
            if (choice3 == '1') {
                cout << "You bravely face the dragon in combat. After a fierce battle, you emerge victorious!" << endl;
            } else {
                cout << "You attempt to sneak past the dragon, but it wakes up and attacks you!" << endl;
            }
        }
    }

    // Determine the ending based on the final decision
    bool rescuedPrincess = (choice1 == '1' && choice2 == '1');
    displayEnding(rescuedPrincess);

    return 0;
}

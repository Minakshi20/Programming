#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Structure to represent a note
struct Note {
    string title;
    string content;
};

// Function to save notes to a file
void saveNotes(const vector<Note>& notes) {
    ofstream file("notes.txt");
    if (!file) {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    for (const Note& note : notes) {
        file << note.title << endl;
        file << note.content << endl;
        file << "----" << endl;
    }

    file.close();
    cout << "Notes saved successfully." << endl;
}

// Function to load notes from a file
vector<Note> loadNotes() {
    ifstream file("notes.txt");
    vector<Note> notes;

    if (!file) {
        cerr << "Note file does not exist. Creating new note file." << endl;
        return notes;
    }

    Note currentNote;
    string line;
    bool readingContent = false;
    while (getline(file, line)) {
        if (line == "----") {
            notes.push_back(currentNote);
            currentNote = Note();
            readingContent = false;
        } else {
            if (!readingContent) {
                currentNote.title = line;
                readingContent = true;
            } else {
                currentNote.content += line + "\n";
            }
        }
    }

    file.close();
    cout << "Notes loaded successfully." << endl;
    return notes;
}

// Function to display all notes
void displayNotes(const vector<Note>& notes) {
    cout << "Notes:" << endl;
    for (size_t i = 0; i < notes.size(); ++i) {
        cout << "Note " << i + 1 << ": " << notes[i].title << endl;
    }
}

// Function to add a new note
void addNote(vector<Note>& notes) {
    Note newNote;
    cout << "Enter note title: ";
    cin.ignore();
    getline(cin, newNote.title);
    cout << "Enter note content: ";
    getline(cin, newNote.content);
    notes.push_back(newNote);
    cout << "Note added successfully." << endl;
}

// Function to edit an existing note
void editNote(vector<Note>& notes) {
    displayNotes(notes);
    int index;
    cout << "Enter the index of the note to edit: ";
    cin >> index;

    if (index >= 1 && index <= static_cast<int>(notes.size())) {
        cout << "Enter new title: ";
        cin.ignore();
        getline(cin, notes[index - 1].title);
        cout << "Enter new content: ";
        getline(cin, notes[index - 1].content);
        cout << "Note edited successfully." << endl;
    } else {
        cout << "Invalid note index." << endl;
    }
}

int main() {
    vector<Note> notes = loadNotes();
    char choice;

    do {
        cout << "\nNote-Taking Application" << endl;
        cout << "1. Display Notes" << endl;
        cout << "2. Add Note" << endl;
        cout << "3. Edit Note" << endl;
        cout << "4. Save Notes" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case '1':
                displayNotes(notes);
                break;
            case '2':
                addNote(notes);
                break;
            case '3':
                editNote(notes);
                break;
            case '4':
                saveNotes(notes);
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

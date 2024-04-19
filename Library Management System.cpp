#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure for Book
struct Book {
    string title;
    string author;
    bool available;
};

// Structure for Borrower
struct Borrower {
    string name;
    vector<string> borrowedBooks;
};

// Function to add a new book to the library
void addBook(vector<Book>& library) {
    Book newBook;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter book author: ";
    getline(cin, newBook.author);
    newBook.available = true;
    library.push_back(newBook);
    cout << "Book added successfully." << endl;
}

// Function to remove a book from the library
void removeBook(vector<Book>& library) {
    string titleToRemove;
    cout << "Enter the title of the book to remove: ";
    cin.ignore();
    getline(cin, titleToRemove);

    bool found = false;
    for (auto it = library.begin(); it != library.end(); ++it) {
        if (it->title == titleToRemove) {
            library.erase(it);
            cout << "Book removed successfully." << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Book not found." << endl;
}

// Function to check book availability
void checkAvailability(const vector<Book>& library) {
    string titleToCheck;
    cout << "Enter the title of the book to check availability: ";
    cin.ignore();
    getline(cin, titleToCheck);

    for (const Book& book : library) {
        if (book.title == titleToCheck) {
            if (book.available)
                cout << "Book is available." << endl;
            else
                cout << "Book is not available." << endl;
            return;
        }
    }
    cout << "Book not found." << endl;
}

int main() {
    vector<Book> library;
    char choice;

    do {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Check Book Availability" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case '1':
                addBook(library);
                break;
            case '2':
                removeBook(library);
                break;
            case '3':
                checkAvailability(library);
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

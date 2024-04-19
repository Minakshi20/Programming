#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure to represent a contact
struct Contact {
    string name;
    string phoneNumber;
    string email;
};

// Function to add a new contact
void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter contact name: ";
    cin.ignore();
    getline(cin, newContact.name);
    cout << "Enter contact phone number: ";
    getline(cin, newContact.phoneNumber);
    cout << "Enter contact email: ";
    getline(cin, newContact.email);
    contacts.push_back(newContact);
    cout << "Contact added successfully." << endl;
}

// Function to update an existing contact
void updateContact(vector<Contact>& contacts) {
    string nameToUpdate;
    cout << "Enter the name of the contact to update: ";
    cin.ignore();
    getline(cin, nameToUpdate);

    for (Contact& contact : contacts) {
        if (contact.name == nameToUpdate) {
            cout << "Enter new phone number: ";
            getline(cin, contact.phoneNumber);
            cout << "Enter new email: ";
            getline(cin, contact.email);
            cout << "Contact updated successfully." << endl;
            return;
        }
    }
    cout << "Contact not found." << endl;
}

// Function to delete a contact
void deleteContact(vector<Contact>& contacts) {
    string nameToDelete;
    cout << "Enter the name of the contact to delete: ";
    cin.ignore();
    getline(cin, nameToDelete);

    for (auto it = contacts.begin(); it != contacts.end(); ++it) {
        if (it->name == nameToDelete) {
            contacts.erase(it);
            cout << "Contact deleted successfully." << endl;
            return;
        }
    }
    cout << "Contact not found." << endl;
}

// Function to view all contacts
void viewContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "No contacts found." << endl;
        return;
    }
    cout << "Contacts:" << endl;
    for (const Contact& contact : contacts) {
        cout << "Name: " << contact.name << endl;
        cout << "Phone Number: " << contact.phoneNumber << endl;
        cout << "Email: " << contact.email << endl;
        cout << "-------------------" << endl;
    }
}

int main() {
    vector<Contact> contacts;
    char choice;

    do {
        cout << "\nContact Management System" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Update Contact" << endl;
        cout << "3. Delete Contact" << endl;
        cout << "4. View Contacts" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case '1':
                addContact(contacts);
                break;
            case '2':
                updateContact(contacts);
                break;
            case '3':
                deleteContact(contacts);
                break;
            case '4':
                viewContacts(contacts);
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

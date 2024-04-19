#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to encrypt or decrypt a file using XOR encryption
void xorEncryptDecryptFile(const string& inputFileName, const string& outputFileName, const string& key) {
    ifstream inputFile(inputFileName, ios::binary);
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return;
    }

    ofstream outputFile(outputFileName, ios::binary);
    if (!outputFile) {
        cerr << "Error: Unable to create output file." << endl;
        return;
    }

    // Get key length
    size_t keyLength = key.length();

    // Encrypt or decrypt the file
    char ch;
    size_t i = 0;
    while (inputFile.get(ch)) {
        // XOR the character with corresponding key character
        ch ^= key[i % keyLength];
        outputFile.put(ch);
        ++i;
    }

    inputFile.close();
    outputFile.close();

    cout << "File " << (outputFileName.empty() ? "encrypted" : "decrypted") << " successfully." << endl;
}

int main() {
    string inputFileName, outputFileName, key;
    char choice;

    cout << "File Encryption/Decryption Tool" << endl;
    cout << "Choose operation:" << endl;
    cout << "1. Encrypt file" << endl;
    cout << "2. Decrypt file" << endl;
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    cout << "Enter input file name: ";
    cin >> inputFileName;

    if (choice == '1') {
        cout << "Enter output file name (leave blank to overwrite input file): ";
        cin >> outputFileName;
        cout << "Enter encryption key: ";
        cin >> key;
        xorEncryptDecryptFile(inputFileName, outputFileName, key);
    } else if (choice == '2') {
        cout << "Enter output file name (leave blank to display decrypted text on console): ";
        cin >> outputFileName;
        cout << "Enter decryption key: ";
        cin >> key;
        xorEncryptDecryptFile(inputFileName, outputFileName, key);
    } else {
        cout << "Invalid choice. Exiting program." << endl;
    }

    return 0;
}

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <openssl/evp.h>
#include <openssl/rand.h>

using namespace std;

// Structure to represent an account entry
struct AccountEntry {
    string website;
    string username;
    string password;
};

// Function to generate a random salt
vector<unsigned char> generateSalt() {
    vector<unsigned char> salt(16);
    if (!RAND_bytes(salt.data(), salt.size())) {
        cerr << "Error: Unable to generate salt." << endl;
        exit(EXIT_FAILURE);
    }
    return salt;
}

// Function to derive a key from a password and salt using PBKDF2
vector<unsigned char> deriveKey(const string& password, const vector<unsigned char>& salt) {
    vector<unsigned char> key(EVP_MAX_KEY_LENGTH);
    if (PKCS5_PBKDF2_HMAC_SHA1(password.c_str(), password.size(), salt.data(), salt.size(), 1000, EVP_MAX_KEY_LENGTH, key.data()) != 1) {
        cerr << "Error: Unable to derive key." << endl;
        exit(EXIT_FAILURE);
    }
    return key;
}

// Function to encrypt data using AES-256-CBC
vector<unsigned char> encryptData(const vector<unsigned char>& data, const vector<unsigned char>& key, const vector<unsigned char>& iv) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        cerr << "Error: Unable to create cipher context." << endl;
        exit(EXIT_FAILURE);
    }

    vector<unsigned char> ciphertext(data.size() + EVP_MAX_BLOCK_LENGTH);
    int len;
    int ciphertextLength;

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv.data()) != 1) {
        cerr << "Error: Unable to initialize encryption." << endl;
        exit(EXIT_FAILURE);
    }

    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, data.data(), data.size()) != 1) {
        cerr << "Error: Unable to perform encryption." << endl;
        exit(EXIT_FAILURE);
    }
    ciphertextLength = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1) {
        cerr << "Error: Unable to finalize encryption." << endl;
        exit(EXIT_FAILURE);
    }
    ciphertextLength += len;

    EVP_CIPHER_CTX_free(ctx);
    ciphertext.resize(ciphertextLength);
    return ciphertext;
}

// Function to decrypt data using AES-256-CBC
vector<unsigned char> decryptData(const vector<unsigned char>& ciphertext, const vector<unsigned char>& key, const vector<unsigned char>& iv) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        cerr << "Error: Unable to create cipher context." << endl;
        exit(EXIT_FAILURE);
    }

    vector<unsigned char> plaintext(ciphertext.size());
    int len;
    int plaintextLength;

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), iv.data()) != 1) {
        cerr << "Error: Unable to initialize decryption." << endl;
        exit(EXIT_FAILURE);
    }

    if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()) != 1) {
        cerr << "Error: Unable to perform decryption." << endl;
        exit(EXIT_FAILURE);
    }
    plaintextLength = len;

    if (EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len) != 1) {
        cerr << "Error: Unable to finalize decryption." << endl;
        exit(EXIT_FAILURE);
    }
    plaintextLength += len;

    EVP_CIPHER_CTX_free(ctx);
    plaintext.resize(plaintextLength);
    return plaintext;
}

// Function to save encrypted account entries to a file
void saveAccounts(const vector<AccountEntry>& accounts, const vector<unsigned char>& key, const vector<unsigned char>& iv) {
    ofstream file("accounts.dat", ios::binary);
    if (!file) {
        cerr << "Error: Unable to open file for writing." << endl;
        exit(EXIT_FAILURE);
    }

    // Encrypt each account entry and write to file
    for (const AccountEntry& account : accounts) {
        // Serialize account entry
        string serializedAccount = account.website + "\n" + account.username + "\n" + account.password + "\n";

        // Encrypt serialized account entry
        vector<unsigned char> encryptedData = encryptData(vector<unsigned char>(serializedAccount.begin(), serializedAccount.end()), key, iv);

        // Write encrypted data to file
        file.write(reinterpret_cast<char*>(encryptedData.data()), encryptedData.size());
    }

    file.close();
    cout << "Accounts saved successfully." << endl;
}

// Function to load and decrypt account entries from a file
vector<AccountEntry> loadAccounts(const string& password, const vector<unsigned char>& iv) {
    ifstream file("accounts.dat", ios::binary);
    if (!file) {
        cerr << "Error: Unable to open file for reading." << endl;
        exit(EXIT_FAILURE);
    }

    // Derive key from password and IV
    vector<unsigned char> salt = iv;
    vector<unsigned char> key = deriveKey(password, salt);

    vector<AccountEntry> accounts;

    // Read and decrypt each account entry from file
    string line;
    while (getline(file, line)) {
        vector<unsigned char> encryptedData(line.begin(), line.end());
        vector<unsigned char> decryptedData = decryptData(encryptedData, key, iv);

        // Deserialize decrypted account entry
        string decryptedAccount(decryptedData.begin(), decryptedData.end());
        istringstream iss(decryptedAccount);
        string website, username, password;
        getline(iss, website);
        getline(iss, username);
        getline(iss, password);

        // Add account entry to vector
        accounts.push_back({website, username, password});
    }

    file.close();
    cout << "Accounts loaded successfully." << endl;
    return accounts;
}

int main() {
    cout << "Password Manager" << endl;

    // Get master password from user
    string masterPassword;
    cout << "Enter master password: ";
    cin >> masterPassword;

    // Generate random IV (Initialization Vector)
    vector<unsigned char> iv = generateSalt();

    // Load accounts from file or create new list if file does not exist
    vector<AccountEntry> accounts;
    ifstream file("accounts.dat", ios::binary);
    if (file) {
        file.close();
        accounts = loadAccounts(masterPassword, iv);
    } else {
        file.close();
        cout << "No accounts found. Creating new account list." << endl;
    }

    char choice;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Add Account" << endl;
        cout << "2

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure to represent a product
struct Product {
    string name;
    string description;
    int stockLevel;
    double price;
};

// Function to add a new product to the inventory
void addProduct(vector<Product>& inventory) {
    Product newProduct;
    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, newProduct.name);
    cout << "Enter product description: ";
    getline(cin, newProduct.description);
    cout << "Enter product stock level: ";
    cin >> newProduct.stockLevel;
    cout << "Enter product price: ";
    cin >> newProduct.price;
    inventory.push_back(newProduct);
    cout << "Product added successfully." << endl;
}

// Function to update an existing product in the inventory
void updateProduct(vector<Product>& inventory) {
    string nameToUpdate;
    cout << "Enter the name of the product to update: ";
    cin.ignore();
    getline(cin, nameToUpdate);

    for (Product& product : inventory) {
        if (product.name == nameToUpdate) {
            cout << "Enter new product description: ";
            getline(cin, product.description);
            cout << "Enter new stock level: ";
            cin >> product.stockLevel;
            cout << "Enter new price: ";
            cin >> product.price;
            cout << "Product updated successfully." << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

// Function to delete a product from the inventory
void deleteProduct(vector<Product>& inventory) {
    string nameToDelete;
    cout << "Enter the name of the product to delete: ";
    cin.ignore();
    getline(cin, nameToDelete);

    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == nameToDelete) {
            inventory.erase(it);
            cout << "Product deleted successfully." << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

// Function to check stock level of a product
void checkStockLevel(const vector<Product>& inventory) {
    string nameToCheck;
    cout << "Enter the name of the product to check stock level: ";
    cin.ignore();
    getline(cin, nameToCheck);

    for (const Product& product : inventory) {
        if (product.name == nameToCheck) {
            cout << "Stock level of " << product.name << ": " << product.stockLevel << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

int main() {
    vector<Product> inventory;
    char choice;

    do {
        cout << "\nInventory Management System" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Update Product" << endl;
        cout << "3. Delete Product" << endl;
        cout << "4. Check Stock Level" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case '1':
                addProduct(inventory);
                break;
            case '2':
                updateProduct(inventory);
                break;
            case '3':
                deleteProduct(inventory);
                break;
            case '4':
                checkStockLevel(inventory);
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

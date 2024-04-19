#include <iostream>

using namespace std;

int main() {
    double num1, num2, result;
    char op;

    // Input the numbers and operation from the user
    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter second number: ";
    cin >> num2;

    cout << "Enter operation (+, -, *, /): ";
    cin >> op;

    // Perform the operation based on the operator
    switch(op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if(num2 != 0)
                result = num1 / num2;
            else {
                cout << "Error! Division by zero." << endl;
                return 1; // Exit with error code
            }
            break;
        default:
            cout << "Invalid operator! Please enter one of +, -, *, /" << endl;
            return 1; // Exit with error code
    }

    // Display the result
    cout << "Result: " << result << endl;

    return 0; // Exit successfully
}



  









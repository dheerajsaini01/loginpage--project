#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User { 
public:
    string username;
    string email;
    string password;
    void signUp();
    void login();
    void forgotPassword();
};

void User::signUp() {
    cout << "Enter your username: ";
    getline(cin, username);

    cout << "Enter your email address: ";
    getline(cin, email);

    cout << "Enter your password: ";
    getline(cin, password);

    // Open the file in append mode to add data to the file
    fstream file("logindata.txt", ios::app | ios::out); 

    if (file.is_open()) {
        file << username << "*" << email << "*" << password << endl;
        file.close();
        cout << "Account created successfully!" << endl;
    } else {
        cout << "Error opening file for sign up." << endl;
    }
}

void User::login() {
    string searchName, searchPass;

    cout << "---------- LOGIN ----------" << endl;

    // First, ask for the username
    cout << "Enter your username: ";
    getline(cin, searchName);

    // After the username, ask for the password
    cout << "Enter your password: ";
    getline(cin, searchPass);

    fstream file("logindata.txt", ios::in); // Open in read mode

    if (file.is_open()) {
        string username, email, password;
        bool loginSuccessful = false;

        // Read the file and check for matching username and password
        while (getline(file, username, '*') && getline(file, email, '*') && getline(file, password, '\n')) {
            if (username == searchName && password == searchPass) {
                cout << "Account login successful!" << endl;
                cout << "Username: " << username << endl;
                loginSuccessful = true;
                break;
            }
        }
        
        // If login is unsuccessful, inform the user
        if (!loginSuccessful) {
            cout << "Invalid username or password." << endl;
        }
        file.close();
    } else {
        cout << "Error opening file for login." << endl;
    }
}

void User::forgotPassword() {
    string searchName, searchEmail;

    cout << "---------- FORGOT PASSWORD ----------" << endl;
    cout << "Enter your username: ";
    getline(cin, searchName);

    cout << "Enter your email address: ";
    getline(cin, searchEmail);

    fstream file("logindata.txt", ios::in); // Open in read mode

    if (file.is_open()) {
        string username, email, password;
        bool accountFound = false;

        while (getline(file, username, '*') && getline(file, email, '*') && getline(file, password, '\n')) {
            if (username == searchName && email == searchEmail) {
                cout << "Account found!" << endl;
                cout << "Your password is: " << password << endl;
                accountFound = true;
                break;
            }
        }
        if (!accountFound) {
            cout << "Account not found." << endl;
        }
        file.close();
    } else {
        cout << "Error opening file for password retrieval." << endl;
    }
}

int main() {
    User obj; 
    char choice;

    do {
        cout << "1. Login" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Forgot Password" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case '1':
                obj.login();
                break;
            case '2':
                obj.signUp();
                break;
            case '3':
                obj.forgotPassword();
                break;
            case '4':
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid selection." << endl;
        }
    } while (choice != '4');

    return 0;
}

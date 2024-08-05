#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <conio.h> // For _getch()

using namespace std;

// File names for storing data
const string adminFile = "admin.txt";
const string availableCarsFile = "available.txt";
const string rentalRecordsFile = "car_rental.txt";
const string userPassFile = "userPass.txt";
const string welcomeFile = "welcome.txt";

// Function prototypes
void displayWelcomeMessage();
void adminMenuActions();
void usermenu();
void userMenu();
void addAdmin();
void showData();
void addCar();
void deleteCar();
void resetAvailableCars();
void loginAdmin();
void loginUser();
void registerUser();
void forgotPassword();
void rentCar();
void viewRentalRecords();
void printInvoice(const string& customerName, const string& carNumber, const string& carModel, int rentalHours, int rentFee,int invoiceNumber);

// Main function
int main() {
    displayWelcomeMessage();

    int choice;
    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Admin Login\n";
        cout << "2. User Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character left by previous input

        switch (choice) {
        case 1:
            adminMenuActions();
            break;
        case 2:
            userMenu();
            break;
        case 3:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}

// Function to display a welcome message
void displayWelcomeMessage() {
    ifstream file(welcomeFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Failed to open welcome file.\n";
    }
}

// Function to handle admin menu actions
void adminMenuActions() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Admin\n";
        cout << "2. Show Data\n";
        cout << "3. Add Car\n";
        cout << "4. Delete Car\n";
        cout << "5. Reset Available Cars\n";
        cout << "6. Log Off\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character left by previous input

        switch (choice) {
        case 1:
            addAdmin();
            break;
        case 2:
            showData();
            break;
        case 3:
            addCar();
            break;
        case 4:
            deleteCar();
            break;
        case 5:
            resetAvailableCars();
            break;
        case 6:
            cout << "Logging off.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 6);
}

// Function to handle user menu actions
void usermenu() {
    int choice;
    while (true) {
        cout << "\nUser Menu:\n";
        cout << "1. Rent a Car\n";
        cout << "2. View Rental Records\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character left by previous input

        switch (choice) {
        case 1:
            rentCar();
            break;
        case 2:
            viewRentalRecords();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}



// Function to handle admin login
void loginAdmin() {
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter password: ";

    // Hide password input
    password = "";
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b"; // Erase the last star
            }
        }
        else {
            password += ch;
            cout << '*'; // Show a star for each character
        }
    }
    cout << endl;

    // Check credentials
    ifstream file(adminFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t delimiterPos = line.find(';');
            if (delimiterPos != string::npos) {
                string storedUsername = line.substr(0, delimiterPos);
                string storedPassword = line.substr(delimiterPos + 1);
                if (storedUsername == username && storedPassword == password) {
                    file.close();
                    adminMenuActions();
                    return;
                }
            }
        }
        file.close();
    }
    cout << "Invalid username or password.\n";
}

// Function to handle user menu
void userMenu() {
    int choice;
    while (true) {
        cout << "\nUser Menu:\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Forgot Password\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            loginUser();
            break;
        case 2:
            registerUser();
            break;
        case 3:
            forgotPassword();
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

// Function to handle user login
void loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";

    // Hide password input
    password = "";
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b"; // Erase the last star
            }
        }
        else {
            password += ch;
            cout << '*'; // Show a star for each character
        }
    }
    cout << endl;

    // Check credentials
    ifstream file(userPassFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t delimiterPos = line.find(';');
            if (delimiterPos != string::npos) {
                string storedUsername = line.substr(0, delimiterPos);
                string storedPassword = line.substr(delimiterPos + 1);
                if (storedUsername == username && storedPassword == password) {
                    file.close();
                    usermenu();
                    return;
                }
            }
        }
        file.close();
    }
    cout << "Invalid username or password.\n";
}

// Function to handle user registration
void registerUser() {
    string username, password;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";

    // Hide password input
    password = "";
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b"; // Erase the last star
            }
        }
        else {
            password += ch;
            cout << '*'; // Show a star for each character
        }
    }
    cout << endl;

    // Append to user file
    ofstream file(userPassFile, ios::app);
    if (file.is_open()) {
        file << username << ";" << password << endl;
        file.close();
        cout << "User registered successfully.\n";
    }
    else {
        cout << "Failed to open user file.\n";
    }
}

// Function to handle forgotten password
void forgotPassword() {
    string username;
    cout << "Enter your username: ";
    cin >> username;

    ifstream file(userPassFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t delimiterPos = line.find(';');
            if (delimiterPos != string::npos) {
                string storedUsername = line.substr(0, delimiterPos);
                if (storedUsername == username) {
                    cout << "Password reset functionality is not implemented.\n";
                    file.close();
                    return;
                }
            }
        }
        file.close();
    }
    cout << "Username not found.\n";
}

// Function to handle car rental
void rentCar() {
    string carNumber;
    int rentalHours;
    string customerName;

    // Show available cars
    ifstream file(availableCarsFile);
    if (file.is_open()) {
        string line;
        cout << "Available Cars:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Failed to open available cars file.\n";
    }

    cout << "Enter Plate number to rent: ";
    cin >> carNumber;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, customerName);

    cout << "Enter number of hours to rent: ";
    cin >> rentalHours;

    // Calculate rent fee (assuming a fixed rate for simplicity)
    int rentFee = rentalHours * 10; // Example rate: 10 $per hour

    int invoiceNumber = rand() % 10000;

    // Generate and print invoice
    printInvoice(customerName, carNumber, "WAJA 1.6", rentalHours, rentFee, invoiceNumber);

    // Record rental
    ofstream rentalFile(rentalRecordsFile, ios::app);
    if (rentalFile.is_open()) {
        rentalFile << customerName << ";" << carNumber << ";" << rentalHours << ";" << rentFee << ";" << invoiceNumber<< endl;
        rentalFile.close();
        cout << "Car rented successfully.\n";
    }
    else {
        cout << "Failed to open rental records file.\n";
    }
}

// Function to print invoice
void printInvoice(const string& customerName, const string& carNumber, const string& carModel, int rentalHours, int rentFee,int invoiceNumber) {
    // Get current time
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);
    
    cout << "\n--- Invoice ---\n";
    cout << "Date: " << put_time(&localTime, "%Y-%m-%d") << endl;
    cout << "Invoice Number: " << invoiceNumber << endl; // Random invoice number for example
    cout << "Customer Name: " << customerName << endl;
    cout << "Car Model: " << carModel << endl;
    cout << "Car Number: " << carNumber << endl;
    cout << "Number of Hours: " << rentalHours << endl;
    cout << "Rental Amount: $" << rentFee << endl;
    cout << "Thank you for renting with us!\n";
}

// Implementation for the missing functions
void addAdmin() {
    // Placeholder: Implement admin addition logic here
    string username, password;
    cout << "Enter new admin username: ";
    cin >> username;
    cout << "Enter new password: ";

    // Hide password input
    password = "";
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b"; // Erase the last star
            }
        }
        else {
            password += ch;
            cout << '*'; // Show a star for each character
        }
    }
    cout << endl;

    // Append to admin file
    ofstream file(adminFile, ios::app);
    if (file.is_open()) {
        file << username << ";" << password << endl;
        file.close();
        cout << "Admin added successfully.\n";
    }
    else {
        cout << "Failed to open admin file.\n";
    }
}

void showData() {
    ifstream file(availableCarsFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Failed to open available cars file.\n";
    }
}

void addCar() {
    string plateNumber, brand, model, color, transmission;
    int capacity, ratePerHour, ratePer12Hours, ratePer24Hours;

    cout << "Enter car details:\n";
    cout << "Plate Number: ";
    cin >> plateNumber;
    cout << "Brand: ";
    cin >> brand;
    cout << "Model: ";
    cin >> model;
    cout << "Capacity: ";
    cin >> capacity;
    cout << "Color: ";
    cin >> color;
    cout << "Transmission: ";
    cin >> transmission;
    cout << "Rate per hour: ";
    cin >> ratePerHour;
    cout << "Rate per 12 hours: ";
    cin >> ratePer12Hours;
    cout << "Rate per 24 hours: ";
    cin >> ratePer24Hours;

    // Append to available cars file
    ofstream file(availableCarsFile, ios::app);
    if (file.is_open()) {
        file << plateNumber << ";" << brand << ";" << model << ";" << capacity << ";" << color << ";" << transmission << ";" << ratePerHour << ";" << ratePer12Hours << ";" << ratePer24Hours << endl;
        file.close();
        cout << "Car added successfully.\n";
    }
    else {
        cout << "Failed to open available cars file.\n";
    }
}

void deleteCar() {
    string carNumber;
    cout << "Enter the car number to delete: ";
    cin >> carNumber;

    ifstream inFile(availableCarsFile);
    ofstream outFile("temp.txt");

    if (inFile.is_open() && outFile.is_open()) {
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            if (line.find(carNumber) != string::npos) {
                found = true;
                continue; // Skip the line with the car number
            }
            outFile << line << endl;
        }
        inFile.close();
        outFile.close();

        remove(availableCarsFile.c_str());
        rename("temp.txt", availableCarsFile.c_str());

        if (found) {
            cout << "Car deleted successfully.\n";
        }
        else {
            cout << "Car not found.\n";
        }
    }
    else {
        cout << "Failed to open files.\n";
    }
}

void resetAvailableCars() {
    // Placeholder: Implement reset available cars logic here
    ofstream file(availableCarsFile, ios::trunc);
    if (file.is_open()) {
        file.close();
        cout << "Available cars list reset.\n";
    }
    else {
        cout << "Failed to open available cars file.\n";
    }
}

void viewRentalRecords() {
    ifstream file(rentalRecordsFile);
    if (file.is_open()) {
        string line;
        cout << "Rental Records:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Failed to open rental records file.\n";
    }
}


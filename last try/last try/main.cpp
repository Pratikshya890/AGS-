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
void adminMenu();
void usermenu();
void userMenu();
void addAdmin();
void showData();
void addCar();
void deleteCar();
void resetAvailableCars();
void loginAdmin();
void registerAdmin();
void AdminforgotPassword();
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
        cout << "\n               \t\t\t\t  --- Main Menu ---\n\n";
       
        cout << setw(60) << "    |------------------|" << endl;
        cout << setw(60) << "1.|   Admin Login    |" << endl;
        cout << setw(60) << "  |------------------|" << endl;
        cout << setw(60) << "2.|   User Login     |" << endl;
        cout << setw(60) << "  |------------------|" << endl;
        cout << setw(60) << "3.|   Exit           |" << endl;
        cout << setw(60) << "  |------------------|" << endl;
      
        cout << "\n\nEnter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character left by previous input

        switch (choice) {
        case 1:
            adminMenu();
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
      

        cout << "\n--------------------------------------------\n";
        cout << "|                Admin Menu                |\n";
        cout << "--------------------------------------------\n";
        cout << "| 1.    Add Admin                          |\n";
        cout << "|------------------------------------------|\n";
        cout << "| 2.    Show Data                          |\n";
        cout << "|------------------------------------------|\n";
        cout << "| 3.    Add Car                            |\n";
        cout << "|------------------------------------------|\n";
        cout << "| 4.    Delete Car                         |\n";
        cout << "|------------------------------------------|\n";
        cout << "| 5.    Reset Available Cars               |\n";
        cout << "|------------------------------------------|\n";
        cout << "| 6.    Log Off                            |\n";
        cout << "--------------------------------------------\n";
        
        
        cout << "\n\nEnter your choice: ";
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
        cout << "\n--------------------------------------\n";
        cout << "|             User Menu              |\n";
        cout << "--------------------------------------\n";
        cout << "| 1.   Rent a Car                    |\n";
        cout << "|------------------------------------|\n";
        cout << "| 2.   View Rental Records           |\n";
        cout << "|------------------------------------|\n";
        cout << "| 3.   Exit                          |\n";
        cout << "--------------------------------------\n";
        cout << "\n\nEnter choice: ";
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



// Function to handle admin menu
void adminMenu() {
    int choice;
    while (true) {
        cout << "\n\t    Admin Menu:\n\n";
        cout << "  |------------------------------|\n";
        cout << "1.|            Login             |\n";
        cout << "  |------------------------------|\n";
        cout << "2.|           Register           |\n";
        cout << "  |------------------------------|\n";
        cout << "3.|       Forgot Password        |\n";
        cout << "  |------------------------------|\n";
        cout << "4.|            Exit              |\n";
        cout << "  |------------------------------|\n";


        cout << "\n\nEnter choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            loginAdmin();
            break;
        case 2:
            registerAdmin();
            break;
        case 3:
            AdminforgotPassword();
            break;
        case 4:
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

// Function to handle admin registration
void registerAdmin() {
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

    // Append to admin file
    ofstream file(adminFile, ios::app);
    if (file.is_open()) {
        file << username << ";" << password << endl;
        file.close();
        cout << "Admin registered successfully.\n";
    }
    else {
        cout << "Failed to open Admin file.\n";
    }
}

// Function to handle forgotten password
void AdminforgotPassword() {
    string username;
    cout << "Enter your username: ";
    cin >> username;

    ifstream file(adminFile);
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

// Function to handle user menu
void userMenu() {
    int choice;
    while (true) {
        cout << "\n\t    User Menu:\n\n";
        cout << "  |------------------------------|\n";
        cout << "1.|            Login             |\n";
        cout << "  |------------------------------|\n";
        cout << "2.|           Register           |\n";
        cout << "  |------------------------------|\n";
        cout << "3.|       Forgot Password        |\n";
        cout << "  |------------------------------|\n";
        cout << "4.|            Exit              |\n";
        cout << "  |------------------------------|\n\n";
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

    cout << "\n\nEnter Plate number to rent: ";
    cin >> carNumber;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, customerName);

    cout << "Enter number of hours to rent: ";
    cin >> rentalHours;

    // Calculate rent fee (assuming a fixed rate for simplicity)
  
    const double ratePerHourNPR = 1000.0; // Example rate: 1200 NPR per hour

    double rentFee = rentalHours * ratePerHourNPR;

    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    int invoiceNumber = rand() % 100;

    // Generate and print invoice
    printInvoice(customerName, carNumber, "WAJA 1.6", rentalHours, rentFee, invoiceNumber);

    // Record rental
    ofstream rentalFile(rentalRecordsFile, ios::app);
    if (rentalFile.is_open()) {
        rentalFile << customerName << ";" << carNumber << ";" << rentalHours << ";"<< rentFee << ";" << invoiceNumber << endl;
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
    
    cout << "\n--------------------------------------------\n";
    cout << "|                 Invoice                  |\n";
    cout << "--------------------------------------------\n";
    cout << "| Date:            " << put_time(&localTime, "%Y-%m-%d") << "              |\n";
    cout << "| Invoice Number:  " << setw(24) << left << invoiceNumber << "|\n";
    cout << "| Customer Name:   " << setw(24) << left << customerName << "|\n";
    cout << "| Car Model:       " << setw(24) << left << carModel << "|\n";
    cout << "| Car Number:      " << setw(24) << left << carNumber << "|\n";
    cout << "| Number of Hours: " << setw(24) << left << rentalHours << "|\n";
    cout << "| Rental Amount:   RS." << setw(23) << left << rentFee << "|\n";
    cout << "--------------------------------------------\n\n";

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
    int capacity = 0, ratePerHour = 0, ratePer12Hours = 0, ratePer24Hours = 0;

    cout << "Enter car details:\n";
    cout << "Plate Number: ";
    cin >> ws; // Clear leading whitespace
    getline(cin, plateNumber);
    cout << "Brand: ";
    getline(cin, brand);
    cout << "Model: ";
    getline(cin, model);
    cout << "Capacity: ";
    cin >> capacity;
    cout << "Color: ";
    cin >> ws; // Clear leading whitespace
    getline(cin, color);
    cout << "Transmission: ";
    getline(cin, transmission);
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


#include "Payment.h"
#include "Constants.h"
#include "Utils.h"
#include "Registration.h"
#include "Venue.h"


#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>

vector<Registration> registrations;


Registration::Registration() : registrationID(0), registrationName(""), ticketAmount(0), registrationCost(0.0) {}

Registration::Registration(int regId, const string& regName, double regCost, int ticAmt)
    : registrationID(regId), registrationName(regName), ticketAmount(ticAmt), registrationCost(regCost){
}

void initializeDefaultRegistration() {
    registrations.clear();

    registrations.push_back(Registration(1, "iPhone 27 Launch", 800, 100.00));
    registrations.push_back(Registration(2, "Samsung Galaxy S30 Launch", 600, 80.00));
    registrations.push_back(Registration(3, "Sony Headphones Launch", 300, 50.00));
    registrations.push_back(Registration(4, "Play Station 6 Launch", 400, 90.00));
    registrations.push_back(Registration(5, "Nintendo Switch 3 Launch", 250, 70.00));
    registrations.push_back(Registration(6, "Yamaha Bike Launch", 150, 30.00));
    registrations.push_back(Registration(7, "Daikin Air Conditioner Launch", 50, 20.00));

    saveRegistrationToFile();
}

void loadRegistrationFromFile() {
    ifstream file(REGISTRATION_FILE);
    if (!file.is_open()) {
        cout << "Creating new registration file with default registration..." << endl;
        initializeDefaultRegistration();
        return;
    }

    registrations.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string item;
        vector<string> tokens;

        while (getline(ss, item, '|')) {
            tokens.push_back(item);
        }

        if (tokens.size() >= 6) {
            Registration registration;
            registration.registrationID = stoi(tokens[0]);
            registration.registrationName = tokens[1];
            registration.ticketAmount = stod(tokens[4]);
            registration.registrationCost = stod(tokens[4]);
            registrations.push_back(registration);
        }
    }
    file.close();
}

void saveRegistrationToFile() {
    ofstream file(REGISTRATION_FILE);
    if (!file.is_open()) {
        cout << "Error: Cannot save registration to file!" << endl;
        return;
    }

    for (const auto& registration : registrations) {
        file << registration.registrationID << "|"
            << registration.registrationName << "|"
            << registration.ticketAmount << "|"
            << registration.registrationCost << "|";
    }
    file.close();
}

void displayAvailableRegistration() {
    cout << "\n" << string(80, '=') << endl;
    cout << "                      AVAILABLE EVENTS" << endl;
    cout << string(80, '=') << endl;
    cout << left << setw(5) << "ID"
        << setw(40) << "Event Name"
        << setw(10) << "Ticket Amount (Available)"
        << setw(15) << "Cost (RM)" << endl;
    cout << string(80, '-') << endl;
}


// Validate venue selection - Your input validation
    int validateRegistrationSelection() {
    int registrationID;
    bool validInput = false;

    do {
        cout << "Enter Registration ID to book (0 to cancel): ";
        if (!(cin >> registrationID)) {
            cout << "Invalid input! Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();

        if (registrationID == 0) return 0;

    } while (!validInput);

    return registrationID;
}

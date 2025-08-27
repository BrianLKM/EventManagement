#pragma once
#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <vector> 
#include <string>
using namespace std;

struct Registration {
    int registrationID;
    string registrationName;
    int ticketAmount;
    double registrationCost;

    Registration();
    Registration(int regid, const string& regName, double regCost, int ticAmt);
};

extern vector<Registration> registrations;

void loadRegistrationFromFile();
void saveRegistrationToFile();
void initializeDefaultRegistration();
int validateRegistrationSelection();

// Display
void displayAvailableRegistrations();

#endif

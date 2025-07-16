#include "CargoAddRecords.h"
#include "../Utils/FileReader.h"
#include "../Cargo/Cargo.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructor
CargoAddRecords::CargoAddRecords(CargoRecords& cr) : fr(cr) {}

// Adds a single cargo record from user input
void CargoAddRecords::addRecord() {
    string id, destination, time, quantity;

    cout << "Enter Cargo ID: ";
    getline(cin, id);
    cout << "Enter Destination: ";
    getline(cin, destination);
    cout << "Enter Time: ";
    getline(cin, time);
    cout << "Enter Quantity: ";
    getline(cin, quantity);

    Cargo c(id, destination, time, stoi(quantity));
    fr.addCargoRecord(c);

    cout << "Cargo record added successfully." << endl;
}

// Adds multiple cargo records from file
void CargoAddRecords::addRecordsFromFile() {
    FileReader frd;
    string fileName;

    cout << "Enter filename to load cargo records from: ";
    cin >> fileName;

    vector<string> lines = frd.readFile(fileName);
    for (const string& line : lines) {
        stringstream ss(line);
        string id, destination, time, quantity;

        getline(ss, id, ',');
        getline(ss, destination, ',');
        getline(ss, time, ',');
        getline(ss, quantity, ',');

        Cargo c(id, destination, time, stoi(quantity));
        fr.addCargoRecord(c);
    }

    cout << "Cargo records loaded successfully from file." << endl;
}

#include "CargoDisplayRecords.h"
#include "../Utils/FileWriter.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Constructor
CargoDisplayRecords::CargoDisplayRecords(IReadCargoRecords* rcr) : readCR(rcr) {}

// Display all cargo records to console
void CargoDisplayRecords::displayRecord() {
    vector<Cargo> cargos = readCR->getAllRecords();
    for (const Cargo& c : cargos) {
        cout << "ID: " << c.getId()
             << ", Destination: " << c.getDestination()
             << ", Time: " << c.getTime()
             << ", Quantity: " << c.getQuantity() << endl;
    }
}

// Save cargo records to a file
void CargoDisplayRecords::saveRecordsToFile() {
    string filename;
    cout << "Enter filename to save cargo records: ";
    cin >> filename;

    vector<Cargo> cargos = readCR->getAllRecords();
    vector<string> lines;

    for (const Cargo& c : cargos) {
        string line = c.getId() + "," + c.getDestination() + "," + c.getTime() + "," + to_string(c.getQuantity());
        lines.push_back(line);
    }

    FileWriter writer;
    writer.writeFile(filename, lines);
    cout << "Cargo records saved to file successfully." << endl;
}

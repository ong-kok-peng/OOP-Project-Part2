/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 18/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "CargoExportData.h"
#include "../FileManager/FileWriter.h"

CargoExportData::CargoExportData(IReadCargoRecords& readCR) : readCR{ readCR } {}

void CargoExportData::exportRecords() {
    cout << "------ Exporting Cargo Records ------\n\n";

    if (readCR.getRecordsSize() == 0) {
        cout << "There are no records. Add a new record or import from a file.\n";
        return;
    }

    cout << "Enter filename to export to: ";
    string filename;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
    getline(cin, filename);

    FileWriter writer(filename, false);
    string header = "ID,Destination,Time,Quantity\n";
    if (!writer.isFileOpened()) {
        cout << "Failed to create file: " << filename << ". File path is invalid. Press enter to go back.\n";
        return;
    }

    writer.writeLine(header); //write header as line 1
    for (int i = 0; i < readCR.getRecordsSize(); ++i) {
        Cargo c = readCR.getCargo(i);
        string line = c.getId() + "," + c.getDestination() + "," + c.getTime() + "," + to_string(c.getQuantity()) + "\n";
        writer.writeLine(line);
    }
    

    cout << "Exported " << readCR.getRecordsSize() << " records successfully to: " << filename << "! Press enter to go back.\n";
}

/* test main code
#include "../Cargo/CargoRecords.h"
#include "../Adders/CargoAddRecords.h"
int main() {
    CargoRecords cr;
    CargoAddRecords addCR(cr); CargoExportData exportCR(cr);

    addCR.addRecord();
    exportCR.exportRecords();

    return 0;
}
*/
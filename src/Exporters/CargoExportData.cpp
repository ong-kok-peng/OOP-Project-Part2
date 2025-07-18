/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 18/7/2025
*/

#include "CargoExportData.h"
#include "../FileManager/FileWriter.h"
#include <iostream>
#include <string>
using namespace std;

CargoExportData::CargoExportData(IReadCargoRecords& readCR) : readCR{ readCR } {}

void CargoExportData::exportRecords() {
    cout << "------ Exporting Cargo Records ------\n\n";

    if (readCR.getRecordsSize() == 0) {
        cout << "There are no records. Add a new record or import from a file.\n";
        return;
    }

    cout << "Enter filename to export to: ";
    string filename;
    cin >> filename;

    FileWriter writer;
    string header = "ID,Destination,Time,Quantity";
    if (!writer.writeToFile(filename, header, false)) {
        cout << "Failed to open file: " << filename << "\n";
        return;
    }

    for (int i = 0; i < readCR.getRecordsSize(); ++i) {
        Cargo c = readCR.getCargo(i);
        string line = c.getId() + "," + c.getDestination() + "," + c.getTime() + "," + to_string(c.getQuantity());
        writer.writeToFile(filename, line, true);
    }

    cout << "Export successful to: " << filename << "\n";
}

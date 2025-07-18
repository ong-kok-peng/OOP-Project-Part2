/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 18/7/2025
*/

#include "FreightExportData.h"
#include "../FileManager/FileWriter.h"
#include <iostream>
#include <string>
using namespace std;

FreightExportData::FreightExportData(IReadFreightRecords& readFR) : readFR{ readFR } {}

void FreightExportData::exportRecords() {
    cout << "------ Exporting Freight Records ------\n\n";

    if (readFR.getRecordsSize() == 0) {
        cout << "There are no records. Add a new record or import from a file.\n";
        return;
    }

    cout << "Enter filename to export to: ";
    string filename;
    cin >> filename;

    FileWriter writer;
    string header = "ID,Name,Capacity";
    if (!writer.writeToFile(filename, header, false)) {
        cout << "Failed to open file: " << filename << "\n";
        return;
    }

    for (int i = 0; i < readFR.getRecordsSize(); ++i) {
        Freight f = readFR.getFreight(i);
        string line = f.getId() + "," + f.getName() + "," + to_string(f.getCapacity());
        writer.writeToFile(filename, line, true);
    }

    cout << "Export successful to: " << filename << "\n";
}

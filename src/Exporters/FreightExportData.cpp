/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 18/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "FreightExportData.h"
#include "../FileManager/FileWriter.h"

FreightExportData::FreightExportData(IReadFreightRecords& readFR) : readFR{ readFR } {}

void FreightExportData::exportRecords() {
	cout << "------ Exporting Freight Records ------\n\n";

	if (readFR.getRecordsSize() == 0) {
		cout << "There are no records. Add a new record or import from a file.\n";
		return;
	}

    cout << "Enter filename to export to: ";
    string filename;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
    getline(cin, filename);

    FileWriter writer(filename, false);
    string header = "ID,Destination,Time,Name\n";
    if (!writer.isFileOpened()) {
        cout << "Failed to create file: " << filename << ". File path is invalid. Press enter to go back.\n";
        return;
    }

    writer.writeLine(header); //write header as line 1
    for (int i = 0; i < readFR.getRecordsSize(); ++i) {
        Freight f = readFR.getFreightByIndex(i);
        string line = f.getId() + "," + f.getDestination() + "," + f.getTime() + "," + f.getName() + "\n";
        writer.writeLine(line);
    }
    writer.closeFile();

    cout << "Exported " << readFR.getRecordsSize() << " records successfully to: " << filename << "! Press enter to go back.\n";
}

/* test main code
#include "../Freight/FreightRecords.h"
#include "../Adders/FreightAddRecords.h"
int main() {
	FreightRecords fr;
	FreightAddRecords addFR(fr); FreightExportData exportFR(fr);

	addFR.addRecord();
	exportFR.exportRecords();

	return 0;
}
*/
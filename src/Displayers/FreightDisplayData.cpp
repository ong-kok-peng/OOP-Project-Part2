/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "FreightDisplayData.h"

FreightDisplayData::FreightDisplayData(IReadFreightRecords& readFR) : readFR{ readFR } {}

void FreightDisplayData::displayData() {
	cout << "------ Displaying Freight Records ------\n\n";

	if (readFR.getRecordsSize() == 0) {
		cout << "There are no records. Add a new record or import from a file.\n";
		return;
	}
    cout << "ID\tDestination\tTime\tFreight Name\n";
    for (int recordIndx = 0; recordIndx < readFR.getRecordsSize(); recordIndx++) {
        Freight therecord = readFR.getFreightByIndex(recordIndx);

        cout << therecord.getId() << "\t";

        if (therecord.getDestination().length() <= 7) { cout << therecord.getDestination() << "\t\t"; }
        else { cout << therecord.getDestination() << "\t"; }

        cout << therecord.getTime() << "\t";

        cout << therecord.getName() << "\n";
    }
    cout << "\n";
}

/*
//uncomment this block if testing sort
void FreightDisplayData::sortRecords() {
    int sortChoice;

    cout << "------ Sort Cargo Records ------\n\n";
    cout << "1. By time\n2. By capacity\nYour choice: ";
    cin >> sortChoice;

    if (cin.fail()) { cout << "Invalid option, press enter to go back.\n"; return; }

    if (sortChoice == 1) { readFR.sortFreightByTime(); }
    if (sortChoice == 2) { readFR.sortFreightByCapacity(); }

    cout << "Sorted! Press enter to go back.\n";
}
*/

/* test main code
#include "../Freight/FreightRecords.h"
#include "../Builders/FreightAddRecords.h"
int main() {
	FreightRecords fr;
	FreightAddRecords addFR(fr); FreightDisplayData displayFR(fr);

	addFR.addRecord();
	displayFR.displayRecords();

	return 0;
}
*/

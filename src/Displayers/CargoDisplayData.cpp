/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "CargoDisplayData.h"

CargoDisplayData::CargoDisplayData(IReadCargoRecords& readCR) : readCR{ readCR } {}

void CargoDisplayData::displayData() {
    cout << "------ Displaying Cargo Records ------\n\n";

    if (readCR.getRecordsSize() == 0) {
        cout << "There are no records. Add a new record or import from a file.\n";
        return;
    }
    cout << "ID\tDestination\tTime\tCargo Quantity\n";
    for (int recordIndx = 0; recordIndx < readCR.getRecordsSize(); recordIndx++) {
        Cargo therecord = readCR.getCargoByIndex(recordIndx);

        cout << therecord.getId() << "\t";

        if (therecord.getDestination().length() <= 7) { cout << therecord.getDestination() << "\t\t"; }
        else { cout << therecord.getDestination() << "\t"; }

        cout << therecord.getTime() << "\t";

        cout << therecord.getQuantity() << "\n";
    }
    cout << "\n";
}

/*
//uncomment this block if testing sort
void CargoDisplayData::sortRecords() {
    int sortChoice;

    cout << "------ Sort Cargo Records ------\n\n";
    cout << "1. By time\n2. By quantity\nYour choice: ";
    cin >> sortChoice;

    if (cin.fail()) { cout << "Invalid option, press enter to go back.\n"; return; }

    if (sortChoice == 1) { readCR.sortCargoByTime(); }
    if (sortChoice == 2) { readCR.sortCargoByQuantity(); }

    cout << "Sorted! Press enter to go back.\n";
}
*/
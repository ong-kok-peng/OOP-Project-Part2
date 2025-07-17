#include <iostream>
#include <string>
using namespace std;

#include "CargoDisplayData.h"

/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

CargoDisplayData::CargoDisplayData(IReadCargoRecords& readCR) : readCR{ readCR } {}

void CargoDisplayData::displayRecords() {
    cout << "------ Displaying Cargo Records ------\n\n";

    if (readCR.getRecordsSize() == 0) {
        cout << "There are no records. Add a new record or import from a file.\n";
        return;
    }
    cout << "ID\tDestination\tTime\tCargo Quantity\n";
    for (int recordIndx = 0; recordIndx < readCR.getRecordsSize(); recordIndx++) {
        Cargo therecord = readCR.getCargo(recordIndx);

        cout << therecord.getId() << "\t";

        if (therecord.getDestination().length() <= 7) { cout << therecord.getDestination() << "\t\t"; }
        else { cout << therecord.getDestination() << "\t"; }

        cout << therecord.getTime() << "\t";

        cout << therecord.getQuantity() << "\n";
    }
    cout << "\n";
}

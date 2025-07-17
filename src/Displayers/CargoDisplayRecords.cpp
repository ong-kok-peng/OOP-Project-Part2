#include <iostream>
#include <string>
using namespace std;

#include "CargoDisplayRecords.h"

CargoDisplayRecords::CargoDisplayRecords(IReadCargoRecords& readCR) : readCR{ readCR } {}

void CargoDisplayRecords::displayRecords() {
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

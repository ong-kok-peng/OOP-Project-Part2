#include <iostream>
#include <string>
using namespace std;

#include "FreightDisplayData.h"

FreightDisplayData::FreightDisplayData(IReadFreightRecords& readFR) : readFR{ readFR } {}

void FreightDisplayData::displayRecords() {
	cout << "------ Displaying Freight Records ------\n\n";

	if (readFR.getRecordsSize() == 0) {
		cout << "There are no records. Add a new record or import from a file.\n";
		return;
	}
    cout << "ID\tDestination\tTime\tFreight Name\n";
    for (int recordIndx = 0; recordIndx < readFR.getRecordsSize(); recordIndx++) {
        Freight therecord = readFR.getFreight(recordIndx);

        cout << therecord.getId() << "\t";

        if (therecord.getDestination().length() <= 7) { cout << therecord.getDestination() << "\t\t"; }
        else { cout << therecord.getDestination() << "\t"; }

        cout << therecord.getTime() << "\t";

        cout << therecord.getName() << "\n";
    }
    cout << "\n";
}
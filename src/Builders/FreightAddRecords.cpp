#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "FreightAddRecords.h"

FreightAddRecords::FreightAddRecords(FreightRecords& fr) : fr{ fr } {}

void FreightAddRecords::addRecord() {
	string textinput, id, destination, time, name;

	cout << "------ Adding New Freight Record ------\n\n";
	cout << "Enter the ID, destination, time and name, separated with a comma in between.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, textinput);

	if (textinput.compare("CANCEL") == 0) { cout << "\nAdd freight is cancelled. Press enter to go back.\n"; return; }
	
	stringstream ss(textinput);
	if (!( getline(ss, id, ',') && getline(ss, destination, ',') 
			&& getline(ss, time, ',') && getline(ss, name))) {
		//if line has < 4 parameters
		cout << "\nBlank input or freight ID/destination/time/name is/are missing. Press enter to go back.\n";
		return; //input failed, skip to next data menu iteration
	}
	else {
		//check if ID exists
		if (fr.getRecordIndex(id) != -1) {
			cout << "Error: ID \"" << id << "\" already exists. Press enter to go back.\n"; return;
		}
		else {
			//validate all values and add freight object to records collection

			bool validationError = false; string errorMsg = "Error: There is/are validation error(s):";

			Freight newRecord;

			//validation error handling
			if (!newRecord.setDestination(destination)) { validationError = true; errorMsg += "\nDestination is empty/invalid format."; }
			if (!newRecord.setTime(time)) { validationError = true; errorMsg += "\nTime is empty/invalid format."; }
			if (!newRecord.setId(id)) { validationError = true; errorMsg += "\nID is empty/invalid format."; }
			if (!newRecord.setName(name)) { validationError = true; errorMsg += "\nName is empty/invalid name."; }

			if (validationError) { cout << errorMsg << "\n\nPress enter to go back\n"; }
			else { fr.addFreight(newRecord); cout << "Success: record is added! Press enter to go back\n"; }
		}
	}
}

void FreightAddRecords::addRecordsFromFile() {

}

/* test main code
int main() {
	FreightRecords fr;
	FreightAddRecords addFR(fr);

	addFR.addRecord();

	return 0;
}
*/
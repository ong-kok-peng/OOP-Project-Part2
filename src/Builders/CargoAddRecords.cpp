#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CargoAddRecords.h"

CargoAddRecords::CargoAddRecords(CargoRecords& cr) : cr{ cr } {}

void CargoAddRecords::addRecord() {
	string textinput, id, destination, time;
	int quantity;
	string quantityStr;

	cout << "------ Adding New Cargo Record ------\n\n";
	cout << "Enter the ID, destination, time and quantity, separated with a comma in between.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, textinput);

	if (textinput.compare("CANCEL") == 0) { cout << "\nAdd cargo is cancelled. Press enter to go back.\n"; return; }

	stringstream ss(textinput);

	if (!(getline(ss, id, ',') && getline(ss, destination, ',')
		&& getline(ss, time, ',') && getline(ss, quantityStr) )) {
		//if line has < 4 parameters
		cout << "\nBlank input or cargo ID/destination/time/quantity is/are missing. Press enter to go back.\n";
		return; //input failed, skip to next data menu iteration
	}
	else {
		//check if ID exists
		if (cr.getRecordIndex(id) != -1) {
			cout << "Error: ID \"" << id << "\" already exists. Press enter to go back.\n"; return;
		}
		else {
			//validate all values and add cargo object to records collection

			bool validationError = false; string errorMsg = "Error: There is/are validation error(s):";

			Cargo newRecord;

			//validation error handling
			if (!newRecord.setDestination(destination)) { validationError = true; errorMsg += "\nDestination is empty/invalid format."; }
			if (!newRecord.setTime(time)) { validationError = true; errorMsg += "\nTime is empty/invalid format."; }
			if (!newRecord.setId(id)) { validationError = true; errorMsg += "\nID is empty/invalid format."; }
			if (!newRecord.setQuantity(stoi(quantityStr))) { validationError = true; errorMsg += "\nQuantity is empty/invalid quantity."; }

			if (validationError) { cout << errorMsg << "\n\nPress enter to go back\n"; }
			else { cr.addCargo(newRecord); cout << "Success: record is added! Press enter to go back\n"; }
		}
	}
}



void CargoAddRecords::addRecordsFromFile() {
	std::cout << "Adding cargo records from file..." << std::endl;
}


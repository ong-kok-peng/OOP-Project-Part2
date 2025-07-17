#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CargoAddRecords.h"

/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

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

		int recordIndex = cr.getRecordIndex(id);
		if (recordIndex != -1) {
			//Existing cargo ID exists. Add quantity instead.

			int additionalQuantity;
			Cargo currentRecord = cr.getCargo(recordIndex);
			cout << "\nThe ID already has original record:\n";
			cout << "Destination: " << currentRecord.getDestination() << "; Time: " << currentRecord.getTime() << "; Quantity: " << currentRecord.getQuantity() << ".\n\n";

			//prompt user whether to key in new quantity or  type 0 to cancel
			cout << "Would you like to add more quantity? Enter additional quantity or 0 to cancel: \n";
			cin >> additionalQuantity;

			if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }
			
			if (additionalQuantity == 0) { cout << "\nAdd cargo is cancelled. Press enter to go back.\n"; }
			if (currentRecord.setQuantity(currentRecord.getQuantity() + additionalQuantity)) { 
				cr.editCargo(recordIndex, currentRecord);
				cout << "\nSuccess: record quantity is appended! Press enter to go back\n"; 
			}
			else { cout << "\nError: additional quantity exceeded max total quantity of 10.\n"; }
		}
		else {
			//Exisitng cargo doesn't exist, make a new record. validate all values and add cargo object to records collection

			bool validationError = false; string errorMsg = "Error: There is/are validation error(s):";

			Cargo newRecord;

			//validation error handling
			if (!newRecord.setDestination(destination)) { validationError = true; errorMsg += "\nDestination is empty/invalid format."; }
			if (!newRecord.setTime(time)) { validationError = true; errorMsg += "\nTime is empty/invalid format."; }
			if (!newRecord.setId(id)) { validationError = true; errorMsg += "\nID is empty/invalid format."; }
			if (!newRecord.setQuantity(stoi(quantityStr))) { validationError = true; errorMsg += "\nInvalid quantity."; }

			if (validationError) { cout << errorMsg << "\n\nPress enter to go back\n"; }
			else { cr.addCargo(newRecord); cout << "Success: record is added! Press enter to go back\n"; }
		}
	}
}



void CargoAddRecords::addRecordsFromFile() {
	std::cout << "Adding cargo records from file..." << std::endl;
}


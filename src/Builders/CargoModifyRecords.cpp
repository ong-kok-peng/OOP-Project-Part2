#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CargoModifyRecords.h"

/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

CargoModifyRecords::CargoModifyRecords(CargoRecords& cr) : cr{ cr } {}

void CargoModifyRecords::editRecord() {
	string textinput, id, oldDestination, oldTime; int oldQuantity;
	string newDestination, newTime, newQuantityStr;

	cout << "------ Edit Existing Cargo Record ------\n\n";
	cout << "Enter the ID you wish to edit.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, textinput);

	if (textinput.compare("CANCEL") == 0) { cout << "\nEdit cargo is cancelled. Press enter to go back.\n"; return; }

	id = textinput;

	//check if ID exists
	int recordIndex = cr.getRecordIndex(id);
	if (recordIndex == -1) {
		cout << "Error: Empty input or the ID \"" << id << "\" does not exist. Press enter to go back.\n"; return;
	}
	else {
		Cargo currentRecord = cr.getCargo(recordIndex);
		oldDestination = currentRecord.getDestination(); oldTime = currentRecord.getTime(); oldQuantity = currentRecord.getQuantity();
		cout << "\nThe original record is:\n";
		cout << "Destination: " << oldDestination << "; Time: " << oldTime << "; Quantity: " << oldQuantity << ".\n\n";

		//prompt user to type new values for the cargo record. if any attribute is unchanged, put a blank
		cout << "Enter the new destination, time and quantity, separated with a comma in between.\n";
		cout << "Leave the value blank if there are no changes. To go back, type \"CANCEL\".\n\n-> ";
		getline(cin, textinput);

		if (textinput.compare("CANCEL") == 0) { cout << "\nEdit cargo is cancelled. Press enter to go back.\n"; return; }

		stringstream ss(textinput);
		if (!(getline(ss, newDestination, ',') && getline(ss, newTime, ',') && getline(ss, newQuantityStr))) {
			//if line has < 3 parameters
			cout << "\nBlank input or new destination/time/quantity is/are missing. Press enter to go back.\n";
			return; //input failed, skip to next data menu iteration
		}
		else {
			// remove white spaces of the new values entered
			newDestination.erase(0, newDestination.find_first_not_of(" \t\r\n")); newDestination.erase(newDestination.find_last_not_of(" \t\r\n") + 1);
			newTime.erase(0, newTime.find_first_not_of(" \t\r\n")); newTime.erase(newTime.find_last_not_of(" \t\r\n") + 1);
			newQuantityStr.erase(0, newQuantityStr.find_first_not_of(" \t\r\n")); newQuantityStr.erase(newQuantityStr.find_last_not_of(" \t\r\n") + 1);

			//only change values that are non empty and validate the values
			bool recordEdited = false; bool validationError = false; string errorMsg = "Error: There is/are validation error(s):";

			if (!newDestination.empty()) {
				recordEdited = true;
				if (!currentRecord.setDestination(newDestination)) { validationError = true; errorMsg += "\nDestination is empty/invalid format."; }
			}
			if (!newTime.empty()) {
				recordEdited = true;
				if (!currentRecord.setTime(newTime)) { validationError = true; errorMsg += "\nTime is empty/invalid format."; }
			}
			if (!newQuantityStr.empty()) {
				recordEdited = true;
				if (!currentRecord.setQuantity( stoi(newQuantityStr) )) { validationError = true; errorMsg += "\nInvalid quantity."; }
			}

			if (recordEdited) {
				if (validationError) { cout << errorMsg << "\n\nPress enter to go back\n"; }
				else { cr.editCargo(recordIndex, currentRecord); cout << "Success: record is edited! Press enter to go back\n"; }
			}
			else { cout << "Record is not edited at all. Press enter to go back"; }
		}
	}
}

void CargoModifyRecords::deleteRecord() {
	string textinput, id, oldDestination, oldTime; int oldQuantity;
	char deleteYesNo;

	cout << "------ Delete Existing Cargo Record ------\n\n";
	cout << "Enter the ID you wish to delete.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, textinput);

	if (textinput.compare("CANCEL") == 0) { cout << "\nDelete cargo is cancelled. Press enter to go back.\n"; return; }

	id = textinput;

	//check if ID exists
	int recordIndex = cr.getRecordIndex(id);
	if (recordIndex == -1) {
		//ID doesn't exist in records, unable to delete
		cout << "Error: Empty input or the ID \"" << id << "\" does not exist. Press enter to go back.\n"; return;
	}
	else {
		//ID exisits in records, check if the quantity is more than 1

		Cargo currentRecord = cr.getCargo(recordIndex);
		oldDestination = currentRecord.getDestination(); oldTime = currentRecord.getTime(); oldQuantity = currentRecord.getQuantity();
		cout << "\nThe original record is:\n";
		cout << "Destination: " << oldDestination << "; Time: " << oldTime << "; Quantity: " << oldQuantity << ".\n\n";

		if (oldQuantity > 1) {
			//old quantity is > 1, prompt user whether to remove some quantity or remove the whole record

			int removeQuantity;
			cout << "Would you like to add more quantity? Enter quantity to remove." << 
				"\nOr enter exact original quantity to delete whole record, or enter 0 to cancel: \n";
			cin >> removeQuantity;

			if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

			if (removeQuantity == 0) { cout << "\nAdd cargo is cancelled. Press enter to go back.\n"; }
			if (removeQuantity == oldQuantity) { cr.deleteCargo(recordIndex); cout << "\nSuccess: record is deleted! Press enter to go back.\n"; }
			
			if (currentRecord.setQuantity(oldQuantity - removeQuantity)) { 
				cr.editCargo(recordIndex, currentRecord);
				cout << "\nSuccess: record quantity is reduced! Press enter to go back\n"; 
			}
			else { cout << "\nError: reduced quantity is less than 0.\n"; }
		}
		else {
			//old quantity is onlly 1, prompt user to confirm delete
			cout << "Are you sure you want to delete this record? (Y/N): ";
			cin >> deleteYesNo;

			if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

			if (deleteYesNo == 'N' || deleteYesNo == 'n') {
				cout << "\nRecord is not deleted. Press enter to go back.\n";
			}
			else if (deleteYesNo == 'Y' || deleteYesNo == 'y') {
				cr.deleteCargo(recordIndex);
				cout << "\nSuccess: record is deleted! Press enter to go back.\n";
			}
			else {
				cout << "\nError: invalid option. Press enter to go back.\n";
			}
		}
		
	}
}


/* test main code
int main() {
	cargoRecords fr;
	cargoModifyRecords modifyFR(fr);

	modifyFR.editRecord();
	modifyFR.deleteRecord();

	return 0;
}
*/

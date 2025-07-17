#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CargoModifyRecords.h"

CargoModifyRecords::CargoModifyRecords(CargoRecords& cr) : cr{ cr } {}

void CargoModifyRecords::editRecord() {
	string textinput, id, oldDestination, oldTime;
	string newDestination, newTime;
	string oldQuantityStr, newQuantityStr;
	int oldQuantity = stoi(oldQuantityStr);
	int newQuantity = stoi(newQuantityStr);

	cout << "------ Edit Existing Cargo Record ------\n\n";
	cout << "Enter the ID you wish to edit.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, textinput);

	if (textinput.compare("CANCEL") == 0) { cout << "\nEdit freight is cancelled. Press enter to go back.\n"; return; }

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

		//prompt user to type new values for the freight record. if any attribute is unchanged, put a blank
		cout << "Enter the new destination, time and quantity, separated with a comma in between.\n";
		cout << "Leave the value blank if there are no changes. To go back, type \"CANCEL\".\n\n-> ";
		getline(cin, textinput);

		if (textinput.compare("CANCEL") == 0) { cout << "\nEdit freight is cancelled. Press enter to go back.\n"; return; }

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
				if (!currentRecord.setQuantity(newQuantity)) { validationError = true; errorMsg += "\nQuantity is empty/invalid quantity."; }
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
	string textinput, id, oldDestination, oldTime, oldQuantity;
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
		cout << "Error: Empty input or the ID \"" << id << "\" does not exist. Press enter to go back.\n"; return;
	}
	else {
		Cargo currentRecord = cr.getCargo(recordIndex);
		oldDestination = currentRecord.getDestination(); oldTime = currentRecord.getTime(); oldQuantity = currentRecord.getQuantity();
		cout << "\nThe original record is:\n";
		cout << "Destination: " << oldDestination << "; Time: " << oldTime << "; Quantity: " << oldQuantity << ".\n\n";

		//prompt user to confirm the delete
		cout << "Are you sure you want to delete this record? (Y/N): ";
		cin >> deleteYesNo;

		if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

		if (deleteYesNo == 'N' || deleteYesNo == 'n') {
			cr.deleteCargo(recordIndex);
			cout << "\nRecord is not deleted. Press enter to go back.\n";
		}
		else if (deleteYesNo == 'Y' || deleteYesNo == 'y') {
			cout << "\nSuccess: record is deleted! Press enter to go back.\n";
		}
		else {
			cout << "\nError: invalid option. Press enter to go back.\n";
		}
	}
}


/* test main code
int main() {
	FreightRecords fr;
	FreightModifyRecords modifyFR(fr);

	modifyFR.editRecord();
	modifyFR.deleteRecord();

	return 0;
}
*/

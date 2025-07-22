/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CargoModifyRecords.h"

CargoModifyRecords::CargoModifyRecords(CargoRecords& cr) : cr{ cr } {}

void CargoModifyRecords::editRecord() {
	string userInput, id, oldDestination, oldTime; int oldQuantity;
	

	cout << "------ Edit Existing Cargo Record ------\n\n";
	cout << "Enter the ID you wish to edit.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, userInput);

	if (userInput.compare("CANCEL") == 0) { cout << "\nEdit cargo is cancelled. Press enter to go back.\n"; return; }

	id = userInput;

	//check if ID exists
	CargoRecords::getRecordOutcome getRecordOutcome = cr.getCargoById(userInput);

	if (getRecordOutcome.status.compare("NOT_FOUND") == 0) {
		//ID doesn't exist, unable to edit record
		cout << "Error: Empty input or the ID \"" << userInput << "\" does not exist. Press enter to go back.\n"; return;
	}
	else if (getRecordOutcome.status.compare("FOUND") == 0) {
		//ID exists, proceed to edit record. Prompt user to type new values for the cargo record. 
		// if any attribute is unchanged, put a blank

		Cargo currentRecord = getRecordOutcome.currentRecord; int recordIndex = getRecordOutcome.index;
		oldDestination = currentRecord.getDestination(); oldTime = currentRecord.getTime(); oldQuantity = currentRecord.getQuantity();
		cout << "\nThe original record is:\n";
		cout << "Destination: " << oldDestination << "; Time: " << oldTime << "; Quantity: " << oldQuantity << ".\n\n";
		cout << "Enter the new destination, time and quantity, separated with a comma in between.\n";
		cout << "Leave the value blank if there are no changes. To go back, type \"CANCEL\".\n\n-> ";
		getline(cin, userInput);

		if (userInput.compare("CANCEL") == 0) { cout << "\nEdit cargo is cancelled. Press enter to go back.\n"; return; }

		CargoRecords::modifyRecordOutcome editCargoOutcome = cr.editCargo(userInput, recordIndex, currentRecord);

		//handle edit record outcome
		if (editCargoOutcome.status.compare("OK") == 0) {
			cout << "Success, record is edited! Press enter to go back\n"; //freight edit success
		}
		else if (editCargoOutcome.status.compare("RECORD_UNCHANGED") == 0) {
			cout << "Record is not edited at all. Press enter to go back\n"; //freight is not edited 
		}
		else if (editCargoOutcome.status.compare("ERROR") == 0) {
			cout << editCargoOutcome.message << "\nPress enter to go back\n"; //freight edit failure, print error message
		}
	}
}

void CargoModifyRecords::deleteRecord() {
	//since cargo with same ID can contain up to 10 quantity, check if quantity is more than 1
	string userInput;
	char deleteYesNo;

	cout << "------ Delete Existing Cargo Record ------\n\n";
	cout << "Enter the ID you wish to delete.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, userInput);

	if (userInput.compare("CANCEL") == 0) { cout << "\nDelete cargo is cancelled. Press enter to go back.\n"; return; }

	//check if ID exists
	CargoRecords::getRecordOutcome getRecordOutcome = cr.getCargoById(userInput);

	if (getRecordOutcome.status.compare("NOT_FOUND") == 0) {
		//ID doesn't exist in records, unable to delete
		cout << "Error: Empty input or the ID \"" << userInput << "\" does not exist. Press enter to go back.\n"; return;
	}
	else if (getRecordOutcome.status.compare("FOUND") == 0) {
		//ID exisits in records

		Cargo currentRecord = getRecordOutcome.currentRecord; int recordIndex = getRecordOutcome.index;
		cout << "\nThe original record is:\n";
		cout << "Destination: " << currentRecord.getDestination() << "; Time: " << currentRecord.getTime() << "; Quantity: " << currentRecord.getQuantity() << ".\n\n";

		if (currentRecord.getQuantity() > 1) {
			//old quantity is > 1, prompt user whether to remove some quantity or remove the whole record

			int removeQuantity;
			cout << "Would you like to remove some quantity? Enter quantity to remove." << 
					"\nOr enter exact original quantity to delete whole record, or enter 0 to cancel: \n";
			cin >> removeQuantity;

			if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

			CargoRecords::modifyRecordOutcome removeCargoOutcome = cr.removeCargo(removeQuantity, recordIndex, currentRecord);

			if (removeCargoOutcome.status.compare("CANCELLED") == 0) {
				cout << "\nRemove cargo cancelled. Press enter to go back.\n";
			}
			if (removeCargoOutcome.status.compare("RECORD_DELETED") == 0) {
				cout << "\ncargo record deleted! Press enter to go back.\n";
			}
			else if (removeCargoOutcome.status.compare("OK") == 0) {
				cout << "\nCargo quantity updated. Press enter to go back.\n";
			}
			else if (removeCargoOutcome.status.compare("ERROR") == 0) {
				cout << removeCargoOutcome.message << " Press enter to go back.\n";
			}
		}
		else {
			//old quantity is only 1, prompt user to confirm delete
			cout << "Are you sure you want to delete this record? (Y/N): ";
			cin >> deleteYesNo;

			if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

			CargoRecords::modifyRecordOutcome deleteRecordOutcome = cr.deleteCargo(recordIndex, deleteYesNo);

			//handle delete record outcome
			if (deleteRecordOutcome.status.compare("OK") == 0) {
				cout << "Success, record is deleted! Press enter to go back\n"; //freight delete success
			}
			else if (deleteRecordOutcome.status.compare("CANCELLED") == 0) {
				cout << "Delete record is cancelled! Press enter to go back\n"; //freight delete cancelled
			}
			else if (deleteRecordOutcome.status.compare("ERROR") == 0) {
				cout << deleteRecordOutcome.message << "\nPress enter to go back\n"; //freight delete failure, print error message
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

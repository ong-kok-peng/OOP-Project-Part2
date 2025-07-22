/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "FreightModifyRecords.h"

FreightModifyRecords::FreightModifyRecords(FreightRecords& fr) : fr{ fr } {}

void FreightModifyRecords::editRecord() {
	string userInput, oldDestination, oldTime, oldName;

	cout << "------ Edit Existing Freight Record ------\n\n";
	cout << "Enter the ID you wish to edit.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, userInput);

	if (userInput.compare("CANCEL") == 0) { cout << "\nEdit freight is cancelled. Press enter to go back.\n"; return; }

	//check if ID exists
	FreightRecords::getRecordOutcome getRecordOutcome = fr.getFreightById(userInput);

	if (getRecordOutcome.status.compare("NOT_FOUND") == 0) {
		cout << "Error: Empty input or the ID \"" << userInput << "\" does not exist. Press enter to go back.\n"; return;
	}
	else if (getRecordOutcome.status.compare("FOUND") == 0) {
		//show user the current record details, and prompt user to type new values for the freight record. 
		//if any attribute is unchanged, put a blank
		Freight currentRecord = getRecordOutcome.currentRecord; int recordIndex = getRecordOutcome.index;
		oldDestination = currentRecord.getDestination(); oldTime = currentRecord.getTime(); oldName = currentRecord.getName();
		cout << "\nThe original record is:\n";
		cout << "Destination: " << oldDestination << "; Time: " << oldTime << "; Name: " << oldName << ".\n\n";
		cout << "Enter the new destination, time and name, separated with a comma in between.\n";
		cout << "Leave the value blank if there are no changes. To go back, type \"CANCEL\".\n\n-> ";
		getline(cin, userInput);

		if (userInput.compare("CANCEL") == 0) { cout << "\nEdit freight is cancelled. Press enter to go back.\n"; return; }

		FreightRecords::modifyRecordOutcome editRecordOutcome = fr.editFreight(userInput, recordIndex, currentRecord);

		//handle edit record outcome
		if (editRecordOutcome.status.compare("OK") == 0) {
			//freight edit success
			cout << "Success, record is edited! Press enter to go back\n";
		}
		else if (editRecordOutcome.status.compare("RECORD_UNCHANGED") == 0) {
			//freight is not edited 
			cout << "Record is not edited at all. Press enter to go back\n";
		}
		else if (editRecordOutcome.status.compare("ERROR") == 0) {
			//freight edit failure, print error message
			cout << editRecordOutcome.message << "\nPress enter to go back\n";
		}
	}
}

void FreightModifyRecords::deleteRecord() {
	string userInput;
	char deleteYesNo;

	cout << "------ Delete Existing Freight Record ------\n\n";
	cout << "Enter the ID you wish to delete.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, userInput);

	if (userInput.compare("CANCEL") == 0) { cout << "\nDelete freight is cancelled. Press enter to go back.\n"; return; }

	//check if ID exists
	FreightRecords::getRecordOutcome getRecordOutcome = fr.getFreightById(userInput);

	if (getRecordOutcome.status.compare("NOT_FOUND") == 0) {
		cout << "Error: Empty input or the ID \"" << userInput << "\" does not exist. Press enter to go back.\n"; return;
	}
	else if (getRecordOutcome.status.compare("FOUND") == 0) {
		//show user the current record details and prompt user to confirm the delete

		Freight currentRecord = getRecordOutcome.currentRecord; int recordIndex = getRecordOutcome.index;
		cout << "\nThe original record is:\n";
		cout << "Destination: " << currentRecord.getDestination() << "; Time: " << currentRecord.getTime() << "; Name: " << currentRecord.getName() << ".\n\n";
		cout << "Are you sure you want to delete this record? (Y/N): ";
		cin >> deleteYesNo;

		if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

		FreightRecords::modifyRecordOutcome deleteRecordOutcome = fr.deleteFreight(recordIndex, deleteYesNo);

		//handle delete record outcome
		if (deleteRecordOutcome.status.compare("OK") == 0) {
			//freight delete success
			cout << "Success, record is deleted! Press enter to go back\n";
		}
		else if (deleteRecordOutcome.status.compare("CANCELLED") == 0) {
			//freight delete cancelled
			cout << "Delete record is cancelled! Press enter to go back\n";
		}
		else if (deleteRecordOutcome.status.compare("ERROR") == 0) {
			//freight delete failure, print error message
			cout << deleteRecordOutcome.message << "\nPress enter to go back\n";
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
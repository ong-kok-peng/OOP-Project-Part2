/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CargoAddRecords.h"
#include "../FileManager/FileReader.h"

CargoAddRecords::CargoAddRecords(CargoRecords& cr) : cr{ cr } {}

void CargoAddRecords::addRecord() {
	//since cargo with same ID can contain up to 10 quantity, check if ID already exists
	//if exists check if quantity is able to append
	string userInput, id;

	cout << "------ Adding New Cargo Record ------\n\n";
	cout << "Enter the ID you wish to add.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, userInput);

	if (userInput.compare("CANCEL") == 0) { cout << "\nEdit cargo is cancelled. Press enter to go back.\n"; return; }

	//check if ID exists
	id = userInput; int recordIndex = cr.getRecordIndex(id);
	if (recordIndex != -1) {
		//Existing cargo ID exists. Add quantity if original quantity from 1 to 9

		Cargo currentRecord = cr.getCargo(recordIndex);
		int oldQuantity = currentRecord.getQuantity(); int addQuantity;

		if (oldQuantity < 10) {
			cout << "\nThe ID already has original record:\n";
			cout << "Destination: " << currentRecord.getDestination() << "; Time: " << currentRecord.getTime() << "; Quantity: " << oldQuantity << ".\n\n";

			//prompt user whether to key in new quantity or  type 0 to cancel
			cout << "Would you like to add more quantity? Enter additional quantity or 0 to cancel: \n";
			cin >> addQuantity;
			if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

			CargoRecords::recordOutcome appendCargoOutcome = cr.appendCargo(addQuantity, recordIndex, currentRecord);

			if (appendCargoOutcome.status.compare("CANCELLED") == 0) {
				cout << "\nAppend cargo cancelled. Press enter to go back.\n";
			}
			else if (appendCargoOutcome.status.compare("OK") == 0) {
				cout << "\nCargo quantity updated. Press enter to go back.\n";
			}
			else if (appendCargoOutcome.status.compare("ERROR") == 0) {
				cout << appendCargoOutcome.message << " Press enter to go back.\n";
			}
		}
		else {
			//existing cargo record has the max quantity already, cannot add new cargo
			cout << "Error: ID \"" << id << "\" has already maximum 10 cargo. Press enter to go back.\n"; return;
		}
	}
	else {
		//cargo ID doesn't exist, ask for details
		cout << "Enter the destination, time and quantity, separated with a comma in between.\n";
		cout << "To go back, type \"CANCEL\".\n\n-> ";

		getline(cin, userInput);
		userInput = id + "," + userInput; //add in ID attribute to the user input

		CargoRecords::recordOutcome addRecordOutcome = cr.addCargo(userInput);

		//handle add record outcome
		if (addRecordOutcome.status.compare("OK") == 0) {
			cout << "\nSuccess, record is added! Press enter to go back\n"; //Cargo add success
		}
		else if (addRecordOutcome.status.compare("ERROR") == 0) {
			cout << "\n" << addRecordOutcome.message << "\nPress enter to go back\n"; //Cargo add failure, print error message
		}
	}
}

void CargoAddRecords::addRecordsFromFile() {
	string userInput;

	cout << "\n------------ Add Cargo Records from File ------------\n\n";
	cout << "Input file path to the cargo data file:\n";
	cout << "If you have previously loaded records, they will be replaced.\nTo go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
	getline(cin, userInput);

	if (userInput.compare("CANCEL") == 0) {
		cout << "\nFile open is cancelled. Press enter to go back.\n"; return; //cancel open
	}

	FileReader readFile(userInput);

	if (!readFile.isFileOpened()) {
		//error in opening the file or no lines were read
		cout << "\"" << userInput << "\" cannot be read. File path is invalid. Press enter to go back.\n";
	}
	else {
		//file can open and read, parse the lines
		string id, destination, time, quantityStr; 
		cout << "\nOpened file " << userInput << "; reading the file now...\n\n";

		cr.clearRecords(); //clearing all the previous records

		int lineNumber = 0;
		string fileLine = readFile.readLine(); //read the first line
		while (fileLine.compare("EOF") != 0) {
			//continuouslly parse line strings as long as the line is not "EOF" (End Of File)

			if (fileLine.compare("blank line") == 0) {
				//current line is blank, move on to the next one
				cout << "Line " << (lineNumber + 1) << ": Blank line..\n";
				continue;
			}
			else {
				//add record from file line
				CargoRecords::recordOutcome addRecordOutcome = cr.addCargo(fileLine);

				//handle add record outcome
				if (addRecordOutcome.status.compare("OK") == 0) {
					//Cargo add success
					cout << "Line " << (lineNumber + 1) << ": Success; record is added!\n";
				}
				else if (addRecordOutcome.status.compare("ERROR") == 0) {
					//Cargo add failure, print error message
					cout << "Line " << (lineNumber + 1) << ": " << addRecordOutcome.message << "\n";
				}
				lineNumber++;
			}
			fileLine = readFile.readLine(); //read the next line 
		}

		cout << "Successfully loaded " << cr.getRecordsSize() << " record(s)! Press enter to go back.\n";
	}
}


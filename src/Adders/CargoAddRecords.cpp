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
	string textinput, id, destination, time;
	int quantity;
	string quantityStr;

	cout << "------ Adding New Cargo Record ------\n\n";
	cout << "Enter the ID, destination, time and quantity, separated with a comma in between.\n";
	cout << "To append quantity of an existing ID, leave destination, time and quantity blank but keep the commas.\n";
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
			//Existing cargo ID exists. Add quantity if original quantity from 1 to 9

			Cargo currentRecord = cr.getCargo(recordIndex);
			int oldQuantity = currentRecord.getQuantity(); int additionalQuantity;

			if (oldQuantity < 10) {
				cout << "\nThe ID already has original record:\n";
				cout << "Destination: " << currentRecord.getDestination() << "; Time: " << currentRecord.getTime() << "; Quantity: " << oldQuantity << ".\n\n";

				//prompt user whether to key in new quantity or  type 0 to cancel
				cout << "Would you like to add more quantity? Enter additional quantity or 0 to cancel: \n";
				cin >> additionalQuantity;

				if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

				if (additionalQuantity == 0) { cout << "\nAdd cargo is cancelled. Press enter to go back.\n"; }
				else if (currentRecord.setQuantity(currentRecord.getQuantity() + additionalQuantity)) {
					cr.editCargo(recordIndex, currentRecord);
					cout << "\nSuccess: record quantity is appended! Press enter to go back\n";
				}
				else { cout << "\nError: additional quantity exceeded max total quantity of 10.\n"; }
			}
			else {
				//existing cargo record has the max quantity already, cannot add new cargo
				cout << "Error: ID \"" << id << "\" has already maximum 10 cargo. Press enter to go back.\n"; return;
			}
		}
		else {
			//Exisitng cargo doesn't exist, make a new record. validate all values and add cargo object to records collection

			bool validationError = false; string errorMsg = "Error: There is/are validation error(s):";

			Cargo newRecord;

			//validation error handling
			if (!newRecord.setDestination(destination)) { validationError = true; errorMsg += "\nDestination is empty/invalid format."; }
			if (!newRecord.setTime(time)) { validationError = true; errorMsg += "\nTime is empty/invalid format."; }
			if (!newRecord.setId(id)) { validationError = true; errorMsg += "\nID is empty/invalid format."; }
			try {
				if (!newRecord.setQuantity(stoi(quantityStr))) { validationError = true; errorMsg += "\nQuantity is not between 1 and 10."; }
			}
			catch (invalid_argument &e) { validationError = true; errorMsg += "\nQuantity is not a number."; }
			

			if (validationError) { cout << errorMsg << "\n\nPress enter to go back\n"; }
			else { cr.addCargo(newRecord); cout << "Success: record is added! Press enter to go back\n"; }
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
				stringstream ss(fileLine);
				if (!(getline(ss, id, ',') && getline(ss, destination, ',')
					&& getline(ss, time, ',') && getline(ss, quantityStr))) {
					//if line has < 4 parameters
					cout << "Line " << (lineNumber + 1) << ": Cargo ID/destination/time/quantity is/are missing.\n";
					continue; //line parsing failed, move on to the next one
				}
				else {
					//validate all values and add cargo object to records collection

					bool validationError = false; string errorMsg = "Line " + to_string(lineNumber + 1) + ": There is/are validation error(s) in ";

					Cargo newRecord;

					//validation error handling
					if (!newRecord.setId(id)) { validationError = true; errorMsg += "ID, "; }
					if (!newRecord.setDestination(destination)) { validationError = true; errorMsg += "Destination, "; }
					if (!newRecord.setTime(time)) { validationError = true; errorMsg += "Time, "; }
					try {
						if (!newRecord.setQuantity(stoi(quantityStr))) { validationError = true; errorMsg += "Quantity"; }
					}
					catch (invalid_argument& e) { validationError = true; errorMsg += "Quantity"; }

					if (validationError) { cout << errorMsg << ".\n"; }
					else { cr.addCargo(newRecord); cout << "Line " << (lineNumber + 1) << ": Success; record is added!\n"; }
				}
				lineNumber++;
			}
			fileLine = readFile.readLine(); //read the next line 
		}

		cout << "Successfully loaded " << cr.getRecordsSize() << " record(s)! Press enter to go back.\n";
	}
}


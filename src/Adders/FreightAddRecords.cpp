/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "FreightAddRecords.h"
#include "../FileManager/FileReader.h"

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
			if (!newRecord.setId(id)) { validationError = true; errorMsg += "\nID is empty/invalid format."; }
			if (!newRecord.setDestination(destination)) { validationError = true; errorMsg += "\nDestination is empty/invalid format."; }
			if (!newRecord.setTime(time)) { validationError = true; errorMsg += "\nTime is empty/invalid format."; }
			if (!newRecord.setName(name)) { validationError = true; errorMsg += "\nName is empty/invalid name."; }

			if (validationError) { cout << errorMsg << "\n\nPress enter to go back\n"; }
			else { fr.addFreight(newRecord); cout << "Success: record is added! Press enter to go back\n"; }
		}
	}
}

void FreightAddRecords::addRecordsFromFile() {
	string userInput;

	cout << "\n------------ Add Freight Records from File ------------\n\n";
	cout << "Input file path to the Freight data file:\n";
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
		string id, destination, time, name;
		cout << "\nOpened file " << userInput << "; reading the file now...\n\n";

		fr.clearRecords(); //clearing all the previous records

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
					&& getline(ss, time, ',') && getline(ss, name))) {
					//if line has < 4 parameters, line parsing failed, move on to the next one
					cout << "Line " << (lineNumber + 1) << ": Freight ID/destination/time/name is/are missing.\n";
					continue; 
				}
				else {
					//validate all values and add freight object to records collection

					bool validationError = false; string errorMsg = "Line " + to_string(lineNumber + 1) + ": There is/are validation error(s) in ";

					Freight newRecord;

					//validation error handling
					if (!newRecord.setId(id)) { validationError = true; errorMsg += "ID, "; }
					if (!newRecord.setDestination(destination)) { validationError = true; errorMsg += "Destination, "; }
					if (!newRecord.setTime(time)) { validationError = true; errorMsg += "Time, "; }
					if (!newRecord.setName(name)) { validationError = true; errorMsg += "Name"; }

					if (validationError) { cout << errorMsg << ".\n"; }
					else { fr.addFreight(newRecord); cout << "Line " << (lineNumber + 1) << ": Success; record is added!\n"; }
				}
				lineNumber++;
			}
			fileLine = readFile.readLine(); //read the next line 
		}
		cout << "Successfully loaded " << fr.getRecordsSize() << " record(s)! Press enter to go back.\n";
	}
}

/* main test code
int main() {
	FreightRecords fr;
	FreightAddRecords addFR(fr);

	addFR.addRecordsFromFile();
	//addFR.addRecord();

	return 0;
}
*/
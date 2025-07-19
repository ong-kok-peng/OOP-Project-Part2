/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "FreightAddRecords.h"
#include "../FileManager/FileReader.h"

FreightAddRecords::FreightAddRecords(FreightRecords& fr) : fr{ fr } {}

void FreightAddRecords::addRecord() {
	string userInput;

	cout << "------ Adding New Freight Record ------\n\n";
	cout << "Enter the ID, destination, time and name, separated with a comma in between.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, userInput);

	if (userInput.compare("CANCEL") == 0) { cout << "\nAdd freight is cancelled. Press enter to go back.\n"; return; }

	FreightRecords::recordOutcome addRecordOutcome = fr.addFreight(userInput);

	//handle add record outcome
	if (addRecordOutcome.status.compare("OK") == 0) {
		//freight add success
		cout << "\nSuccess, record is added! Press enter to go back\n";
	}
	else if (addRecordOutcome.status.compare("ERROR") == 0) {
		//freight add failure, print error message
		cout << "\n" << addRecordOutcome.message << "\nPress enter to go back\n";
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
				FreightRecords::recordOutcome addRecordOutcome = fr.addFreight(fileLine);

				//handle add record outcome
				if (addRecordOutcome.status.compare("OK") == 0) {
					//freight add success
					cout << "Line " << (lineNumber + 1) << ": Success; record is added!\n";
				}
				else if (addRecordOutcome.status.compare("ERROR") == 0) {
					//freight add failure, print error message
					cout << "Line " << (lineNumber + 1) << ": " << addRecordOutcome.message << "\n";
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
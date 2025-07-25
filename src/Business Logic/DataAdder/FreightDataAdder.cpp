/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "FreightDataAdder.h"

FreightDataAdder::FreightDataAdder(I_AddFreightDataPool& fp) : fp { fp } {}

DataAdder::addOutcome FreightDataAdder::addData(string input) {
	addOutcome ao;

	//parse user input
	string id, destination, time, name;

	if (input == "CANCEL") { ao.status = "CANCELLED"; ao.message = "Adding data is cancelled."; return ao; }

	if (input.empty()) { ao.status = "ERROR"; ao.message = "User input is blank."; return ao; } //blank input

	stringstream ss(input);
	if (!(getline(ss, id, ',') && getline(ss, destination, ',')
		&& getline(ss, time, ',') && getline(ss, name))) {
		//if line has < 4 parameters, input is invalid
		ao.status = "ERROR"; ao.message = "freight ID/destination/time/name is/are missing."; return ao;
	}
	else {
		//check if ID exists; a non empty indexes vector should be returned if ID already exists.
		if (!fp.getFreightIndexsByValue(id).empty()) {
			//indexes are found with the entered ID, hence ID already exists.
			ao.status = "ERROR"; ao.message = "ID already exists."; return ao;
		}
		else {
			//create a freightdata object if ID doesn't exist, then if validation passed, add to data pool

			FreightData freightData;
			TransportEntity::validationOutcome vo = freightData.setValues(id, destination, time, name);
			if (vo.validationPass) {
				fp.addFreight(freightData);
				ao.status = "SUCCESS"; ao.message = "freight data is added!"; return ao; //add record success
			}
			else { 
				ao.status = "ERROR"; ao.message = "Validation error(s) in: " + vo.message; return ao; //add record failed validation
			}
		}
	}
}

DataAdder::addOutcome FreightDataAdder::importFromFile(string input) {
	addOutcome io;

	if (input=="CANCEL") {
		io.status = "CANCELLED";  io.message = "File import is cancelled.";
		return io;
	}

	FileReader readFile(input);

	if (!readFile.isFileOpened()) {
		//error in opening the file or no lines were read
		io.status = "ERROR";  io.message = "\"" + input + "\" cannot be read. File path is invalid.";
	}
	else {
		//file can open and read, parse the lines

		fp.clearAllFreight(); // clear all the data in the pool
		//from this point onwards, io.message is a multiline output

		io.status = "SUCCESS"; //assume successful, if any line has error change to READ_WITH_ERRORS
		io.message = "Importing file " + input + "...\n";

		int lineNumber = 1; int dataAddedCount = 0;
		string fileLine = readFile.readLine(); //read the first line
		while (fileLine.compare("EOF") != 0) {
			//continuouslly parse line strings as long as the line is not "EOF" (End Of File)

			if (fileLine.compare("blank line") == 0) {
				//current line is blank, move on to the next one
				io.status = "READ_WITH_ERRORS";
				io.message += "Line " + to_string(lineNumber) + ": Blank line\n";
			}
			else {
				DataAdder::addOutcome ao = addData(fileLine);

				//handle add record outcome
				if (ao.status == "SUCCESS") {
					//freight add success
					io.message += "Line " + to_string(lineNumber) + ": " + ao.message + "\n";
					dataAddedCount++; //only increment if file line add data is successful
				}
				else if (ao.status == "ERROR") {
					//some certain freight has error in the fileline
					io.status = "READ_WITH_ERRORS";
					io.message += "Line " + to_string(lineNumber) + ": " + ao.message + "\n";
				}
			}
			lineNumber++;
			fileLine = readFile.readLine(); //read the next line 
		}

		io.message += "Successfully added " + to_string(dataAddedCount) + " data(s)!";
	}
	return io;
}

/* main test code
int main() {
	FreightDataPool fr;
	FreightDataAdder addFR(fr);

	//add individual data
	DataAdder::addOutcome ao1 = addFR.addData("F45,Honolulu,1256,megaCarrier");
	cout << ao1.status << "; " << ao1.message << endl;
	DataAdder::addOutcome ao2 = addFR.addData("F34, Tokyo,2134, megacarrier");
	cout << ao2.status << "; " << ao2.message << endl;
	DataAdder::addOutcome ao3 = addFR.addData("F88, Pyong Yang, 0905, cargoCruISER");
	cout << ao3.status << "; " << ao3.message << endl;
	
	//import from file
	DataAdder::addOutcome io =  addFR.importFromFile("cargo and freight data files\\freightdata.csv");
	cout << "File import: " << io.status << "\n" << io.message << endl;

	return 0;
}
*/
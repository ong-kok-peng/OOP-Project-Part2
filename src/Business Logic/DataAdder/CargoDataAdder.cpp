/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CargoDataAdder.h"

CargoDataAdder::CargoDataAdder(CargoDataPool& cp) : cp{ cp } {}

DataAdder::addOutcome CargoDataAdder::addData(string input) {
	addOutcome ao;

	//parse user input
	string id, destination, time, quantity;

	//CANCEL and blank checks are not needed because the UI already passes ID at least into user input

	stringstream ss(input);
	if (!(getline(ss, id, ',') && getline(ss, destination, ',')
		&& getline(ss, time, ',') && getline(ss, quantity))) {
		//if line has < 4 parameters, input is invalid
		ao.status = "ERROR"; ao.message = "Cargo ID/destination/time/quantity is/are missing."; return ao;
	}
	else {
		//check if ID exists; a non empty indexes vector should be returned if ID already exists.
		if (!cp.getCargoIndexsByValue(id).empty()) {
			//indexes are found with the entered ID, hence ID already exists.
			ao.status = "ERROR"; ao.message = "ID already exists."; return ao;
		}
		else {
			//create a Cargodata object if ID doesn't exist, then if validation passed, add to data pool

			CargoData cargoData;
			TransportEntity::validationOutcome vo = cargoData.setValues(id, destination, time, quantity);
			if (vo.validationPass) {
				cp.addCargo(cargoData);
				ao.status = "SUCCESS"; ao.message = "Cargo data is added!"; return ao; //add record success
			}
			else {
				ao.status = "ERROR"; ao.message = "Validation error(s) in: " + vo.message; return ao; //add record failed validation
			}
		}
	}
}

DataAdder::addOutcome CargoDataAdder::importFromFile(string input) {
	addOutcome io;

	if (input == "CANCEL") {
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

		cp.clearAllCargo(); // clear all the data in the pool
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
					//Cargo add success
					io.message += "Line " + to_string(lineNumber) + ": " + ao.message + "\n";
					dataAddedCount++; //only increment if file line add data is successful
				}
				else if (ao.status == "ERROR") {
					//some certain Cargo has error in the fileline
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
	CargoDataPool cr;
	CargoDataAdder addCR(cr);

	//add individual data
	DataAdder::addOutcome ao1 = addCR.addData("C45,Honolulu,1256,3");
	cout << ao1.status << "; " << ao1.message << endl;
	DataAdder::addOutcome ao2 = addCR.addData("C34, Tokyo,2134, 7");
	cout << ao2.status << "; " << ao2.message << endl;
	DataAdder::addOutcome ao3 = addCR.addData("C88, Pyong Yang, 0905, 10");
	cout << ao3.status << "; " << ao3.message << endl;


	//import from file
	DataAdder::addOutcome io =  addFR.importFromFile("cargo and freight data files\\cargodata.csv");
	cout << "\nFile import: " << io.status << "\n" << io.message << endl;

	return 0;
}
*/
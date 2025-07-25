/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "FreightDataModifier.h"

FreightDataModifier::FreightDataModifier(I_ModifyFreightDataPool& fp) : fp{ fp } {}

DataModifier::modifyOutcome FreightDataModifier::editData(int index, string input) {
	modifyOutcome mo;

	//parse user input
	string id, oldDestination, oldTime, oldName;
	string newDestination, newTime, newName;

	if (input == "CANCEL") { mo.status = "CANCELLED"; mo.message = "Editing data is cancelled."; return mo; }

	if (input.empty()) { mo.status = "ERROR"; mo.message = "User input is blank."; return mo; } //blank input

	stringstream ss(input);
	if (!(getline(ss, newDestination, ',') && getline(ss, newTime, ',') && getline(ss, newName))) {
		//if line has < 3 parameters, input is invalid
		mo.status = "ERROR"; mo.message = "new destination/time/name is/are missing."; return mo;
	}
	else {
		// remove white spaces of the new values entered
		newDestination.erase(0, newDestination.find_first_not_of(" \t\r\n")); newDestination.erase(newDestination.find_last_not_of(" \t\r\n") + 1);
		newTime.erase(0, newTime.find_first_not_of(" \t\r\n")); newTime.erase(newTime.find_last_not_of(" \t\r\n") + 1);
		newName.erase(0, newName.find_first_not_of(" \t\r\n")); newName.erase(newName.find_last_not_of(" \t\r\n") + 1);

		//retreive existing freight old values from the index; in case index is invalid, return status DATA_DOESNT_EXIST
		FreightData* _getF = fp.getFreightByIndex(index);
		if (_getF == nullptr) { mo.status = "DATA_DOESNT_EXIST"; return mo; }
		else {
			FreightData getF = *_getF;
			id = getF.getId(); oldDestination = getF.getDestination(); oldTime = getF.getTime(); oldName = getF.getName();

			//if the new values are non empty, update those values to the old values
			bool isDataModified = false;

			if (!newDestination.empty()) {
				isDataModified = true; oldDestination = newDestination;
			}
			if (!newTime.empty()) {
				isDataModified = true; oldTime = newTime;
			}
			if (!newName.empty()) {
				isDataModified = true; oldName = newName;
			}

			if (!isDataModified) {
				//parameters from input are empty, hence record not edited
				mo.status = "RECORD_UNCHANGED"; mo.message = "Record is not edited at all"; return mo;
			}
			else {
				//if record is modified, create a new freight with updated and old values if unchanged
				FreightData newData;
				TransportEntity::validationOutcome vo = newData.setValues(id, oldDestination, oldTime, oldName);
				if (vo.validationPass) {
					fp.editFreight(index, newData);
					mo.status = "SUCCESS"; mo.message = "freight data is edited!"; return mo; //edit record success
				}
				else {
					mo.status = "ERROR"; mo.message = "Validation error(s) in: " + vo.message; return mo; //edit record failed validation
				}
			}
		}
	}
}

DataModifier::modifyOutcome FreightDataModifier::deleteData(int index, char yesNo) {
	modifyOutcome mo;

	//retreive existing freight from the index; in case index is invalid, return status DATA_DOESNT_EXIST
	FreightData* _getF = fp.getFreightByIndex(index);
	if (_getF == nullptr) { mo.status = "DATA_DOESNT_EXIST"; mo.message = "Index returns no data."; return mo; }

	if (yesNo == 'N' || yesNo == 'n') {
		mo.status = "CANCELLED"; mo.message = "Deletion is cancelled."; return mo; //delete cancelled
	}
	else if (yesNo == 'Y' || yesNo == 'y') {
		fp.deleteFreight(index); //delete confirmed
		mo.status = "OK"; mo.message = "Deletion is successful!"; return mo;
	}
	else {
		mo.status = "ERROR"; mo.message = "invalid user input. Please select yes or no."; return mo;
	}
	return mo;
}

/* main test code
#include "../DataAdder/FreightDataAdder.h"
#include "../DataDisplayer/FreightDataDisplayer.h"

int main() {
	FreightDataPool fr;
	FreightDataAdder addFR(fr); FreightDataModifier modFR(fr); FreightDataDisplayer displayFR(fr);

	//add individual data
	DataAdder::addOutcome ao1 = addFR.addData("F45,Honolulu,1256,megaCarrier");
	cout << ao1.status << "; " << ao1.message << endl;
	DataAdder::addOutcome ao2 = addFR.addData("F34, Tokyo,2134, megacarrier");
	cout << ao2.status << "; " << ao2.message << endl;
	DataAdder::addOutcome ao3 = addFR.addData("F88, Pyong Yang, 0905, cargoCruISER");
	cout << ao3.status << "; " << ao3.message << endl;

	//display original data
	int index = 0; DataDisplayer::dataValues dv1 = displayFR.getDataValues(index);
	cout << "Original data:\n";
	while (dv1.status != "NO_DATA") {
		cout << "Index " << index << ": ";
		cout << "ID is " << dv1.id << "; capacity is " << dv1.extraVal2 << "; name is " << dv1.extraVal1;
		cout << "; Destination is " << dv1.destination << "; time is " << dv1.time << "\n\n";
		dv1 = displayFR.getDataValues(++index); //increment index and then get the next data value
	}

	//edit two data
	DataModifier::modifyOutcome mo1 = modFR.editData(1, ", 1447, ");
	if (mo1.status == "DATA_DOESNT_EXIST") { cout << "Wrong index input.\n"; }
	else { cout << mo1.status << "; " << mo1.message << "\n"; }

	DataModifier::modifyOutcome mo2 = modFR.editData(0, "Chicago, , minimover");
	if (mo2.status == "DATA_DOESNT_EXIST") { cout << "Wrong index input.\n"; }
	else { cout << mo2.status << "; " << mo2.message << "\n"; }

	//delete one data
	int indexToDel = 2;
	DataModifier::modifyOutcome do1 = modFR.deleteData(indexToDel, 'n');
	if(do1.status == "DATA_DOESNT_EXIST") { cout << "Wrong index input.\n"; }
	else { cout << do1.status << "; " << do1.message << "\n"; }

	//display modified data
	index = 0; DataDisplayer::dataValues dv2 = displayFR.getDataValues(index);
	cout << "Updated data:\n";
	while (dv2.status != "NO_DATA") {
		cout << "Index " << index << ": ";
		cout << "ID is " << dv2.id << "; capacity is " << dv2.extraVal2 << "; name is " << dv2.extraVal1;
		cout << "; Destination is " << dv2.destination << "; time is " << dv2.time << "\n\n";
		dv2 = displayFR.getDataValues(++index); //increment index and then get the next data value
	}

	return 0;
}
*/
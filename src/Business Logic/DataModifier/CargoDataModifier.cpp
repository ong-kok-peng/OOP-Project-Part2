/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CargoDataModifier.h"

CargoDataModifier::CargoDataModifier(CargoDataPool& cp) : cp{ cp } {}

DataModifier::modifyOutcome CargoDataModifier::editData(int index, string input) {
	modifyOutcome mo;

	//parse user input
	string id, oldDestination, oldTime, oldQuantity;
	string newDestination, newTime, newQuantity;

	if (input == "CANCEL") { mo.status = "CANCELLED"; mo.message = "Editing data is cancelled."; return mo; }

	if (input.empty()) { mo.status = "ERROR"; mo.message = "User input is blank."; return mo; } //blank input

	stringstream ss(input);
	if (!(getline(ss, newDestination, ',') && getline(ss, newTime, ',') && getline(ss, newQuantity))) {
		//if line has < 3 parameters, input is invalid
		mo.status = "ERROR"; mo.message = "new destination/time/quantity is/are missing."; return mo;
	}
	else {
		// remove white spaces of the new values entered
		newDestination.erase(0, newDestination.find_first_not_of(" \t\r\n")); newDestination.erase(newDestination.find_last_not_of(" \t\r\n") + 1);
		newTime.erase(0, newTime.find_first_not_of(" \t\r\n")); newTime.erase(newTime.find_last_not_of(" \t\r\n") + 1);
		newQuantity.erase(0, newQuantity.find_first_not_of(" \t\r\n")); newQuantity.erase(newQuantity.find_last_not_of(" \t\r\n") + 1);

		//retreive existing Cargo old values from the index; in case index is invalid, return status DATA_DOESNT_EXIST
		CargoData* _getF = cp.getCargoByIndex(index);
		if (_getF == nullptr) { mo.status = "DATA_DOESNT_EXIST"; return mo; }
		else {
			CargoData getF = *_getF;
			id = getF.getId(); oldDestination = getF.getDestination(); oldTime = getF.getTime(); oldQuantity = to_string(getF.getQuantity());

			//if the new values are non empty, update those values to the old values
			bool isDataModified = false;

			if (!newDestination.empty()) {
				isDataModified = true; oldDestination = newDestination;
			}
			if (!newTime.empty()) {
				isDataModified = true; oldTime = newTime;
			}
			if (!newQuantity.empty()) {
				isDataModified = true; oldQuantity = newQuantity;
			}

			if (!isDataModified) {
				//parameters from input are empty, hence record not edited
				mo.status = "RECORD_UNCHANGED"; mo.message = "Record is not edited at all"; return mo;
			}
			else {
				//if record is modified, create a new Cargo with updated and old values if unchanged
				CargoData newData;
				TransportEntity::validationOutcome vo = newData.setValues(id, oldDestination, oldTime, oldQuantity);
				if (vo.validationPass) {
					cp.editCargo(index, newData);
					mo.status = "SUCCESS"; mo.message = "Cargo data is edited!"; return mo; //edit record success
				}
				else {
					mo.status = "ERROR"; mo.message = "Validation error(s) in: " + vo.message; return mo; //edit record failed validation
				}
			}
		}
	}
}

DataModifier::modifyOutcome CargoDataModifier::deleteData(int index, char yesNo) {
	modifyOutcome mo;

	//retreive existing Cargo from the index; in case index is invalid, return status DATA_DOESNT_EXIST
	CargoData* _getF = cp.getCargoByIndex(index);
	if (_getF == nullptr) { mo.status = "DATA_DOESNT_EXIST"; mo.message = "Index returns no data."; return mo; }

	if (yesNo == 'N' || yesNo == 'n') {
		mo.status = "CANCELLED"; mo.message = "Deletion is cancelled."; return mo; //delete cancelled
	}
	else if (yesNo == 'Y' || yesNo == 'y') {
		cp.deleteCargo(index); //delete confirmed
		mo.status = "OK"; mo.message = "Deletion is successful!"; return mo;
	}
	else {
		mo.status = "ERROR"; mo.message = "invalid user input. Please select yes or no."; return mo;
	}
	return mo;
}

/* main test code
#include "../DataAdder/CargoDataAdder.h"
#include "../DataDisplayer/CargoDataDisplayer.h"

int main() {
	CargoDataPool cr;
	CargoDataAdder addCR(cr); CargoDataModifier modCR(cr); CargoDataDisplayer displayCR(cr);

	//add individual data
	DataAdder::addOutcome ao1 = addCR.addData("C45,Honolulu,1256, 3");
	cout << ao1.status << "; " << ao1.message << endl;
	DataAdder::addOutcome ao2 = addCR.addData("C34, Tokyo,2134, 5 ");
	cout << ao2.status << "; " << ao2.message << endl;
	DataAdder::addOutcome ao3 = addCR.addData("C88, Pyong Yang, 0905, 9");
	cout << ao3.status << "; " << ao3.message << endl;

	//display original data
	int index = 0; DataDisplayer::dataValues dv1 = displayCR.getDataValues(index);
	cout << "Original data:\n";
	while (dv1.status != "NO_DATA") {
		cout << "Index " << index << ": ";
		cout << "ID is " << dv1.id << "; capacity is " << dv1.extraVal2 << "; Quantity is " << dv1.extraVal1;
		cout << "; Destination is " << dv1.destination << "; time is " << dv1.time << "\n\n";
		dv1 = displayCR.getDataValues(++index); //increment index and then get the next data value
	}

	//edit two data
	DataModifier::modifyOutcome mo1 = modCR.editData(1, ", 1447, ");
	if (mo1.status == "DATA_DOESNT_EXIST") { cout << "Wrong index input.\n"; }
	else { cout << mo1.status << "; " << mo1.message << "\n"; }

	DataModifier::modifyOutcome mo2 = modCR.editData(0, "Chicago, , 10");
	if (mo2.status == "DATA_DOESNT_EXIST") { cout << "Wrong index input.\n"; }
	else { cout << mo2.status << "; " << mo2.message << "\n"; }

	//delete one data
	int indexToDel = 2;
	DataModifier::modifyOutcome do1 = modCR.deleteData(indexToDel, 'n');
	if(do1.status == "DATA_DOESNT_EXIST") { cout << "Wrong index input.\n"; }
	else { cout << do1.status << "; " << do1.message << "\n"; }

	//display modified data
	index = 0; DataDisplayer::dataValues dv2 = displayCR.getDataValues(index);
	cout << "Updated data:\n";
	while (dv2.status != "NO_DATA") {
		cout << "Index " << index << ": ";
		cout << "ID is " << dv2.id << "; capacity is " << dv2.extraVal2 << "; Quantity is " << dv2.extraVal1;
		cout << "; Destination is " << dv2.destination << "; time is " << dv2.time << "\n\n";
		dv2 = displayCR.getDataValues(++index); //increment index and then get the next data value
	}

	return 0;
}
*/
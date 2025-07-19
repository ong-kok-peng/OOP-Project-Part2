/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/


#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CargoRecords.h"

CargoRecords::CargoRecords() {
	records = {};
}

// displayer functions
int CargoRecords::getRecordsSize() { return records.size(); }

Cargo CargoRecords::getCargo(int index) { return records[index]; }

void CargoRecords::sortCargoByTime() {

}

void CargoRecords::sortCargoByQuantity() {

}

// builder functions
int CargoRecords::getRecordIndex(string id) {
	auto iterator = find_if(records.begin(), records.end(), [id](Cargo& c) {
		return id.compare(c.getId()) == 0;
		});

	if (iterator != records.end()) {
		return (distance(records.begin(), iterator));
	}
	else { return -1; }
}

// if user adds cargo of same ID (already exists), call appendCargo()
// otherwise if ID never exists, just addCargo()
CargoRecords::recordOutcome CargoRecords::addCargo(string userInput) {
	//parse user input
	string id, destination, time, quantityStr; int quantity;
	recordOutcome ro;

	if (userInput.empty()) { ro.status = "ERROR"; ro.message = "Error: user input is blank."; return ro; } //blank input

	stringstream ss(userInput);

	if (!(getline(ss, id, ',') && getline(ss, destination, ',')
		&& getline(ss, time, ',') && getline(ss, quantityStr))) {
		//if line has < 4 parameters, input is invalid
		ro.status = "ERROR"; ro.message = "Error: cargo ID/destination/time/quantity is/are missing."; return ro;
	}
	else {
		//exisiting ID dont need to check because its already checked in builders

		bool validationError = false; //assume no validation error
		string errorMsg = "Error: There is/are validation error(s) in ";

		Cargo newRecord;

		//validation error handling
		if (!newRecord.setId(id)) { validationError = true; errorMsg += "ID, "; }
		if (!newRecord.setDestination(destination)) { validationError = true; errorMsg += "destination, "; }
		if (!newRecord.setTime(time)) { validationError = true; errorMsg += "time, "; }
		try {
			if (!newRecord.setQuantity(stoi(quantityStr))) { validationError = true; errorMsg += "quantity."; }
		}
		catch (invalid_argument& e) { validationError = true; errorMsg += "quantity."; }

		if (!validationError) { records.push_back(newRecord); ro.status = "OK"; return ro; } //add records success
		else { ro.status = "ERROR"; ro.message = errorMsg; return ro; } //add records failed validation

	}
}

CargoRecords::recordOutcome CargoRecords::appendCargo(int addQuantity, int index, Cargo currentRecord) {
	//parse user input
	recordOutcome ro;

	if (addQuantity == 0) { 
		ro.status = "CANCELLED"; return ro; //append cargo is cancelled
	}
	else if (currentRecord.setQuantity(currentRecord.getQuantity() + addQuantity)) {
		records.erase(records.begin() + index);
		records.insert(records.begin() + index, currentRecord);
		ro.status = "OK"; return ro; //Success: record quantity is appended!;
	}
	else { 
		//append quantity failed
		ro.status = "ERROR"; ro.message = "Error: additional quantity exceeded max total quantity of 10."; return ro;
	}
}

// if user deletes cargo that has quantity > 1, call removeCargo()
// if delete entire cargo, call function deleteCargo()
CargoRecords::recordOutcome CargoRecords::deleteCargo(int index, char deleteYesNo) {
	//parse user input
	recordOutcome ro;

	if (deleteYesNo == 'N' || deleteYesNo == 'n') {
		ro.status = "CANCELLED"; return ro; //delete cancelled
	}
	else if (deleteYesNo == 'Y' || deleteYesNo == 'y') {
		records.erase(records.begin() + index); //delete confirmed
		ro.status = "OK"; return ro;
	}
	else {
		ro.status = "ERROR"; ro.message = "Error: invalid user input. Please select yes or no."; return ro;
	}
}

CargoRecords::recordOutcome CargoRecords::removeCargo(int removeQuantity, int index, Cargo currentRecord) {
	//parse user input
	recordOutcome ro;

	if (removeQuantity == 0) {
		ro.status = "CANCELLED"; return ro; //remove cargo is cancelled
	}
	else if (currentRecord.getQuantity() == removeQuantity) {
		records.erase(records.begin() + index); //delete whole record, since remove quantity is equal to original quantity
		ro.status = "RECORD_DELETED"; return ro;
	}
	else if (currentRecord.setQuantity(currentRecord.getQuantity() - removeQuantity)) {
		records.erase(records.begin() + index);
		records.insert(records.begin() + index, currentRecord);
		ro.status = "OK"; return ro; //Success: record quantity is appended!;
	}
	else {
		//remove quantity failed
		ro.status = "ERROR"; ro.message = "Error: reduced quantity cannot be lesser than 1."; return ro;
	}
}

CargoRecords::recordOutcome CargoRecords::editCargo(string userInput, int index, Cargo currentRecord) {
	//parse user input
	string newDestination, newTime, newQuantityStr;
	recordOutcome ro;

	if (userInput.empty()) { ro.status = "RECORD_UNCHANGED"; return ro; } //blank input, hence record not edited

	stringstream ss(userInput);
	if (!(getline(ss, newDestination, ',') && getline(ss, newTime, ',') && getline(ss, newQuantityStr))) {
		//if line has < 3 parameters
		ro.status = "ERROR"; ro.message = "Blank input or new destination/time/quantity is/are missing."; return ro;
	}
	else {
		// remove white spaces of the new values entered
		newDestination.erase(0, newDestination.find_first_not_of(" \t\r\n")); newDestination.erase(newDestination.find_last_not_of(" \t\r\n") + 1);
		newTime.erase(0, newTime.find_first_not_of(" \t\r\n")); newTime.erase(newTime.find_last_not_of(" \t\r\n") + 1);
		newQuantityStr.erase(0, newQuantityStr.find_first_not_of(" \t\r\n")); newQuantityStr.erase(newQuantityStr.find_last_not_of(" \t\r\n") + 1);

		//only change values that are non empty and validate the values
		bool recordEdited = false; bool validationError = false; string errorMsg = "Error: There is/are validation error(s):";

		if (!newDestination.empty()) {
			recordEdited = true;
			if (!currentRecord.setDestination(newDestination)) { validationError = true; errorMsg += "\nDestination is empty/invalid format."; }
		}
		if (!newTime.empty()) {
			recordEdited = true;
			if (!currentRecord.setTime(newTime)) { validationError = true; errorMsg += "\nTime is empty/invalid format."; }
		}
		if (!newQuantityStr.empty()) {
			try {
				recordEdited = true;
				if (!currentRecord.setQuantity(stoi(newQuantityStr))) { validationError = true; errorMsg += "\nInvalid quantity."; }
			}
			catch (invalid_argument& e) { validationError = true; errorMsg += "quantity."; }
		}

		if (recordEdited) {
			if (validationError) { ro.status = "ERROR"; ro.message = errorMsg; return ro; }//edit records failed validation
			else {
				//edit records success
				records.erase(records.begin() + index);
				records.insert(records.begin() + index, currentRecord);
				ro.status = "OK"; return ro;
			}
		}
		//parameters from input are empty, hence record not edited
		else { ro.status = "RECORD_UNCHANGED"; return ro; }
	}
}

void CargoRecords::clearRecords() { records.clear(); }
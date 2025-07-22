/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

#include "FreightRecords.h"

FreightRecords::FreightRecords() {
	records = {};
}

// displayer functions
int FreightRecords::getRecordsSize() { return records.size(); }

Freight FreightRecords::getFreightByIndex(int index) { return records[index]; }

FreightRecords::getRecordOutcome FreightRecords::getFreightById(string id) {
	getRecordOutcome ro;

	auto iterator = find_if(records.begin(), records.end(), [id](Freight& c) {
		return id.compare(c.getId()) == 0;
		});

	if (iterator != records.end()) {
		int index = distance(records.begin(), iterator);
		ro.status = "FOUND"; ro.index = index; ro.currentRecord = records[index]; return ro;
	}
	else { ro.status = "NOT_FOUND"; return ro; }
}

void FreightRecords::sortFreightByTime() {
	//sort by ascending destination order, with ascending time order so as to priortize earliest freight
	sort(records.begin(), records.end(), [](Freight& prevFreight, Freight& nextFreight) {
		bool equalDestination = prevFreight.getDestination().compare(nextFreight.getDestination()) == 0;

		return (prevFreight.getDestination() < nextFreight.getDestination()) ||
			(equalDestination && prevFreight.getTime() < nextFreight.getTime());
		});
}

void FreightRecords::sortFreightByCapacity() {
	//sort by ascending destination order, with descending capacity order so as to fill in as many cargo as possible.
	sort(records.begin(), records.end(), [](Freight& prevFreight, Freight& nextFreight) {
		bool equalDestination = prevFreight.getDestination().compare(nextFreight.getDestination()) == 0;

		return (prevFreight.getDestination() < nextFreight.getDestination()) ||
			(equalDestination && prevFreight.getCapacity() > nextFreight.getCapacity());
		});
}

// builder functions
FreightRecords::modifyRecordOutcome FreightRecords::addFreight(string userInput) {
	//parse user input
	string id, destination, time, name;
	modifyRecordOutcome ro; 
	
	if (userInput.empty()) { ro.status = "ERROR"; ro.message = "Error: user input is blank."; return ro; } //blank input

	stringstream ss(userInput);
	if (!(getline(ss, id, ',') && getline(ss, destination, ',')
		&& getline(ss, time, ',') && getline(ss, name))) {
		 //if line has < 4 parameters, input is invalid
		ro.status = "ERROR"; ro.message = "Error: freight ID/destination/time/name is/are missing."; return ro;
	}
	else {
		//check if ID exists
		if (getFreightById(id).status.compare("FOUND") == 0) {
			 //ID already exists.
			ro.status = "ERROR"; ro.message = "Error: ID already exists."; return ro;
		}
		else if (getFreightById(id).status.compare("NOT_FOUND") == 0) {
			//validate all values and add freight object to records collection

			Freight newRecord;
			bool validationError = false; //assume no validation error
			string errorMsg = "Error: There is/are validation error(s) in ";

			//validation error handling
			if (!newRecord.setId(id)) { validationError = true; errorMsg += "ID, "; }								//ID is empty/invalid format.
			if (!newRecord.setDestination(destination)) { validationError = true; errorMsg += "destination, "; }	//Destination is empty/invalid format.
			if (!newRecord.setTime(time)) { validationError = true; errorMsg += "time, "; }							//Time is empty/invalid format.
			if (!newRecord.setName(name)) { validationError = true; errorMsg += "name."; }							//Name is empty / invalid name.

			if (!validationError) { records.push_back(newRecord); ro.status = "OK"; return ro; } //add records success
			else { ro.status = "ERROR"; ro.message = errorMsg; return ro; } //add records failed validation
		}
	}
}

FreightRecords::modifyRecordOutcome FreightRecords::deleteFreight(int index, char deleteYesNo) {
	//parse user input
	modifyRecordOutcome ro;

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

FreightRecords::modifyRecordOutcome FreightRecords::editFreight(string userInput, int index, Freight currentRecord) {
	//parse user input
	string newDestination, newTime, newName;
	modifyRecordOutcome ro;

	if(userInput.empty()) { ro.status = "RECORD_UNCHANGED"; return ro; } //blank input, hence record not edited

	stringstream ss(userInput);
	if (!(getline(ss, newDestination, ',') && getline(ss, newTime, ',') && getline(ss, newName))) {
		//if line has < 3 parameters, input is invalid
		ro.status = "ERROR"; ro.message = "Blank input or new destination/time/name is/are missing."; return ro;
	}
	else {
		// remove white spaces of the new values entered
		newDestination.erase(0, newDestination.find_first_not_of(" \t\r\n")); newDestination.erase(newDestination.find_last_not_of(" \t\r\n") + 1);
		newTime.erase(0, newTime.find_first_not_of(" \t\r\n")); newTime.erase(newTime.find_last_not_of(" \t\r\n") + 1);
		newName.erase(0, newName.find_first_not_of(" \t\r\n")); newName.erase(newName.find_last_not_of(" \t\r\n") + 1);

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
		if (!newName.empty()) {
			recordEdited = true;
			if (!currentRecord.setName(newName)) { validationError = true; errorMsg += "\nName is empty/invalid name."; }
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

void FreightRecords::clearRecords() { records.clear(); }
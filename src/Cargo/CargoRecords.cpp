/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/


#include <iostream>
#include <string>
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

// if user adds cargo of same ID (already exists), prompt user to append cargo, with the extra quantity input
// otherwise if ID never exists, just addCargo()
void CargoRecords::addCargo(Cargo c) {
	records.push_back(c);
}

// if user deletes cargo that has quantity > 1, prompt user to choose if delete whole cargo record or some cargo quantity
// if delete entire cargo, call function deleteCargo()
void CargoRecords::deleteCargo(int index) {
	records.erase(records.begin() + index);
}

void CargoRecords::editCargo(int index, Cargo c) {
	records.erase(records.begin() + index);
	records.insert(records.begin() + index, c);
}

void CargoRecords::clearRecords() { records.clear(); }
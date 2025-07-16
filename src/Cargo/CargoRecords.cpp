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

// if user adds cargo of same id (already exists), prompt user to append cargo, with the extra quantity input
// then setQuantity(old quantity + extra quantity)
// otherwise if id never exists, just addCargo()
void CargoRecords::addCargo(Cargo c) {
	records.push_back(c);
}

bool CargoRecords::appendCargo(int index, int quantity) {
	Cargo therecord = records[index];
	return therecord.setQuantity(therecord.getQuantity() + quantity);
}

// if user deletes cargo that has quantity > 1, prompt user to choose if delete whole cargo record or some cargo quantity
// if delete entire cargo, call function deleteCargo()
// if only delete some quantity call function removeCargo()
void CargoRecords::deleteCargo(int index) {
	records.erase(records.begin() + index);
}

bool CargoRecords::removeCargo(int index, int quantity) {
	Cargo therecord = records[index];
	return therecord.setQuantity(therecord.getQuantity() - quantity);
}

void CargoRecords::editCargo(int index, Cargo c) {
	records.erase(records.begin() + index);
	records.insert(records.begin() + index, c);
}

// Edit existing cargo record at the given index
void CargoRecords::editCargoRecord(int index, Cargo c) {
    if (index >= 0 && index < records.size()) {
        records[index] = c;
    } else {
        std::cerr << "Invalid index." << std::endl;
    }
}

// Delete cargo record at the given index
void CargoRecords::deleteCargoRecord(int index) {
    if (index >= 0 && index < records.size()) {
        records.erase(records.begin() + index);
    } else {
        std::cerr << "Invalid index." << std::endl;
    }
}

std::vector<Cargo> CargoRecords::getAllRecords() const {
    return records;
}

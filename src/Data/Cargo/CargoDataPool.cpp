/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

#include "CargoDataPool.h"

CargoDataPool::CargoDataPool() {
	freights = {};
}

void CargoDataPool::addCargo(CargoData f) {
	freights.push_back(f);
}

void CargoDataPool::editCargo(int index, CargoData f) {
	freights.erase(freights.begin() + index);
	freights.insert(freights.begin() + index, f);
}

void CargoDataPool::deleteCargo(int index) {
	freights.erase(freights.begin() + index);
}

int CargoDataPool::getCargoIndexById(string id) {
	auto iterator = find_if(freights.begin(), freights.end(), [id](CargoData& f) {
		return (id == f.getId());
		});

	if (iterator != freights.end()) {
		int index = distance(freights.begin(), iterator);
		return index;
	}
	else { return -1; }
}

CargoData* CargoDataPool::getCargoByIndex(int index) {
	if (index >= 0 && index < freights.size()) {
		return &(freights[index]);
	}
	else {
		return nullptr;
	}
}

void CargoDataPool::clearAllCargo() {
	freights.clear();
}

void CargoDataPool::sortByTime() {
	//sort by ascending destination order, with ascending time order so as to priortize earliest freight
	sort(freights.begin(), freights.end(), [](CargoData& prevCargo, CargoData& nextCargo) {
		bool equalDestination = prevCargo.getDestination().compare(nextCargo.getDestination()) == 0;

		return (prevCargo.getDestination() < nextCargo.getDestination()) ||
			(equalDestination && prevCargo.getTime() < nextCargo.getTime());
		});
}

void CargoDataPool::sortByCapacity() {
	//sort by ascending destination order, with descending capacity order so as to fill in as many cargo as possible.
	sort(freights.begin(), freights.end(), [](CargoData& prevCargo, CargoData& nextCargo) {
		bool equalDestination = prevCargo.getDestination().compare(nextCargo.getDestination()) == 0;

		return (prevCargo.getDestination() < nextCargo.getDestination()) ||
			(equalDestination && prevCargo.getQuantity() > nextCargo.getQuantity());
		});
}

/* test main code
int main() {
	CargoDataPool c_dataPool;

	CargoData c1;
	TransportEntity::validationOutcome vo1 = c1.setValues("C01", "HONOLULU", "1456", "4");
	if (vo1.validationPass) {
		c_dataPool.addCargo(c1); cout << "1. Added!\n";
	}
	else { cout << "1. Validation error(s) in: " << vo1.message << endl; }

	CargoData c2;
	TransportEntity::validationOutcome vo2 = c2.setValues("C34", "Tokyo", "2134", "7");
	if (vo2.validationPass) {
		c_dataPool.addCargo(c2); cout << "2. Added!\n";
	}
	else { cout << "2. Validation error(s) in: " << vo2.message << endl; }

	CargoData c3;
	TransportEntity::validationOutcome vo3 = c3.setValues("C01", "Pyong Yang", "0905", "10");
	if (vo3.validationPass) {
		c_dataPool.addCargo(c3); cout << "3. Added!\n";
	}
	else { cout << "3. Validation error(s) in: " << vo3.message << endl; }

	CargoData* _getC = c_dataPool.getCargoByIndex(0);
	if (_getC == nullptr) { cout << "No cargo data at this index.\n"; }
	else {
		CargoData getC = *_getC;
		cout << "ID is " << getC.getId() << "; quantity is " << getC.getQuantity();
		cout << "; Destination is " << getC.getDestination() << "; time is " << getC.getTime() << endl;
	}

	return 0;
}
*/
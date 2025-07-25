/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

#include "FreightDataPool.h"

FreightDataPool::FreightDataPool() {
	freights = {};
}

void FreightDataPool::addFreight(FreightData f) {
	freights.push_back(f);
}

void FreightDataPool::editFreight(int index, FreightData f) {
	freights.erase(freights.begin() + index);
	freights.insert(freights.begin() + index, f);
}

void FreightDataPool::deleteFreight(int index) {
	freights.erase(freights.begin() + index);
}

vector<int> FreightDataPool::getFreightIndexsByValue(string value) {
	vector<int> indexs = {};

	auto iterator = freights.begin();
	iterator = find_if(iterator, freights.end(), [value](FreightData& f) {
		return ( value == f.getId() || value == f.getDestination() || value == f.getTime() || value == f.getName() );
		});

	while (iterator != freights.end()) {
		indexs.push_back(distance(freights.begin(), iterator));
		iterator = find_if(++iterator, freights.end(), [value](FreightData& f) {
			return ( value == f.getId() || value == f.getDestination() || value == f.getTime() || value == f.getName() );
			});
	}

	return indexs;
}

FreightData* FreightDataPool::getFreightByIndex(int index) {
	if (index >= 0 && index < freights.size()) {
		return &(freights[index]);
	}
	else {
		return nullptr;
	}
}

void FreightDataPool::clearAllFreight() {
	freights.clear();
}

void FreightDataPool::sortByTime() {
	//sort by ascending destination order, with ascending time order so as to priortize earliest freight
	sort(freights.begin(), freights.end(), [](FreightData& prevFreight, FreightData& nextFreight) {
		bool equalDestination = prevFreight.getDestination().compare(nextFreight.getDestination()) == 0;

		return (prevFreight.getDestination() < nextFreight.getDestination()) ||
			(equalDestination && prevFreight.getTime() < nextFreight.getTime());
		});
}

void FreightDataPool::sortByCapacity() {
	//sort by ascending destination order, with descending capacity order so as to fill in as many cargo as possible.
	sort(freights.begin(), freights.end(), [](FreightData& prevFreight, FreightData& nextFreight) {
		bool equalDestination = prevFreight.getDestination().compare(nextFreight.getDestination()) == 0;

		return (prevFreight.getDestination() < nextFreight.getDestination()) ||
			(equalDestination && prevFreight.getCapacity() > nextFreight.getCapacity());
		});
}

/* test main code
int main() {
	FreightDataPool f_dataPool;

	FreightData f1;
	TransportEntity::validationOutcome vo1 = f1.setValues("F01", "HONOLULU", "1456", "cargoCruiser");
	if (vo1.validationPass) {
		f_dataPool.addFreight(f1); cout << "1. Added!\n";
	}
	else { cout << "1. Validation error(s) in: " << vo1.message << endl; }

	FreightData f2;
	TransportEntity::validationOutcome vo2 = f2.setValues("F34", "Tokyo", "2134", "megacarrier");
	if (vo2.validationPass) {
		f_dataPool.addFreight(f2); cout << "2. Added!\n";
	}
	else { cout << "2. Validation error(s) in: " << vo2.message << endl; }

	FreightData f3;
	TransportEntity::validationOutcome vo3 = f3.setValues("F88", "Pyong Yang", "0905", "minimover");
	if (vo3.validationPass) {
		f_dataPool.addFreight(f3); cout << "3. Added!\n";
	}
	else { cout << "3. Validation error(s) in: " << vo3.message << endl; }

	FreightData* _getF2 = f_dataPool.getFreightByIndex(2);
	if (_getF2 == nullptr) { cout << "No freight data at this index.\n"; }
	else {
		FreightData getF2 = *_getF2;
		cout << "ID is " << getF2.getId() << "; capacity is " << getF2.getCapacity() << "; name is " << getF2.getName();
		cout << "; Destination is " << getF2.getDestination() << "; time is " << getF2.getTime() << endl;
	}

	return 0;
}
*/
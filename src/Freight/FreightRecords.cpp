#include <iostream>
#include <string>
using namespace std;

#include "FreightRecords.h"

FreightRecords::FreightRecords() {
	records = {};
}

// displayer functions
int FreightRecords::getRecordsSize() { return records.size(); }

Freight FreightRecords::getFreight(int index) { return records[index]; }

void FreightRecords::sortFreightByTime() {

}

void FreightRecords::sortFreightByQuantity() {

}

// builder functions
int FreightRecords::getRecordIndex(string id) {
	auto iterator = find_if(records.begin(), records.end(), [id](Freight& f) {
		return id.compare(f.getId()) == 0;
		});

	if (iterator != records.end()) {
		return (distance(records.begin(), iterator));
	}
	else { return -1; }
}

void FreightRecords::addFreight(Freight f) {
	records.push_back(f);
}

void FreightRecords::deleteFreight(int index) {
	records.erase(records.begin() + index);
}

void FreightRecords::editFreight(int index, Freight f) {
	records.erase(records.begin() + index);
	records.insert(records.begin() + index, f);
}

void FreightRecords::clearRecords() { records.clear(); }
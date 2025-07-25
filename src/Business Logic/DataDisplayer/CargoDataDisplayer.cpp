/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "CargoDataDisplayer.h"

CargoDataDisplayer::CargoDataDisplayer(I_DisplayCargoDataPool& cp) : cp{ cp } {}

DataDisplayer::searchOutcome CargoDataDisplayer::searchData(string input) {
	searchOutcome so;

	if (input == "CANCEL") { so.status = "CANCELLED"; return so; }

	//populate cargo data indexs if value matches any attribute inside the data pool
	vector<int> indexs = cp.getCargoIndexsByValue(input);
	if (!indexs.empty()) {
		so.status = "DATA_FOUND"; so.indexs.insert(so.indexs.end(), indexs.begin(), indexs.end());
	}
	else {
		so.status = "DATA_NOT_FOUND";
	}

	return so;
}

DataDisplayer::dataValues CargoDataDisplayer::getDataValues(int index) {
	dataValues dv;

	CargoData* _getC = cp.getCargoByIndex(index);
	if (_getC == nullptr) { dv.status = "NO_DATA"; }
	else {
		CargoData getC = *_getC;
		dv.id = getC.getId(); dv.destination = getC.getDestination(); dv.time = getC.getTime();
		dv.extraVal1 = to_string(getC.getQuantity()); //extra value 1 will be the Cargo quantity
	}

	return dv;
}

/* main test code
#include "../DataAdder/CargoDataAdder.h"
#include "../../Data/Cargo/CargoDataPool.h"

int main() {
	CargoDataPool cr;
	CargoDataAdder addCR(cr); CargoDataDisplayer displayCR(cr);

	//add individual data
	DataAdder::addOutcome ao1 = addCR.addData("C45,Honolulu,1256,5");
	cout << ao1.status << "; " << ao1.message << endl;
	DataAdder::addOutcome ao2 = addCR.addData("C34, Tokyo,2134, 10");
	cout << ao2.status << "; " << ao2.message << endl;
	DataAdder::addOutcome ao3 = addCR.addData("C88, Pyong Yang, 0905, 1");
	cout << ao3.status << "; " << ao3.message << endl;
	DataAdder::addOutcome ao4 = addCR.addData("C99, Tokyo, 1755, 6");
	cout << ao4.status << "; " << ao4.message << endl;

	//search data
	DataDisplayer::searchOutcome so1 = displayCR.searchData("Tokyo");
	vector<int> searchIndexs1 = so1.indexs;

	if (so1.status == "DATA_FOUND") { 
		cout << "Search found, at index(s) ";
		for (auto& index : searchIndexs1) {
			cout << index << ",";
		}
		cout << "\n"; 
	}
	else if (so1.status == "DATA_NOT_FOUND") { cout << "Search not found.\n"; }

	//display data
	int index = 0; DataDisplayer::dataValues dv = displayCR.getDataValues(index);

	while (dv.status != "NO_DATA") {
		cout << "Index " << index << ": ";
		cout << "ID is " << dv.id << "; quantity is " << dv.extraVal1;
		cout << "; Destination is " << dv.destination << "; time is " << dv.time << "\n\n";
		dv = displayCR.getDataValues(++index); //increment index and then get the next data value
	}

	return 0;
}
*/
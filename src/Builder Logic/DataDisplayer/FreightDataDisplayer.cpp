/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "FreightDataDisplayer.h"

FreightDataDisplayer::FreightDataDisplayer(FreightDataPool& fp) : fp{ fp } {}

DataDisplayer::searchOutcome FreightDataDisplayer::searchData(string input) {
	searchOutcome so;

	//check if ID exists; a non -1 index should be returned if ID already exists.
	int index = fp.getFreightIndexById(input);
	if (index != -1) {
		so.status = "DATA_FOUND"; so.index = index;
	}
	else {
		so.status = "DATA_NOT_FOUND";
	}

	return so;
}

DataDisplayer::dataValues FreightDataDisplayer::getDataValues(int index) {
	dataValues dv;

	FreightData* _getF = fp.getFreightByIndex(index);
	if (_getF == nullptr) { dv.status = "NO_DATA"; }
	else {
		FreightData getF = *_getF;
		dv.id = getF.getId(); dv.destination = getF.getDestination(); dv.time = getF.getTime(); 
		dv.extraVal1 = getF.getName(); //extra value 1 will be the freight name
		dv.extraVal2 = to_string(getF.getCapacity()); //extra value 2 will be the freight capacity
	}

	return dv;
}

/* main test code
#include "../DataAdder/FreightDataAdder.h"

int main() {
	FreightDataPool fr;
	FreightDataAdder addFR(fr); FreightDataDisplayer displayFR(fr);

	//add individual data
	DataAdder::addOutcome ao1 = addFR.addData("F45,Honolulu,1256,megaCarrier");
	cout << ao1.status << "; " << ao1.message << endl;
	DataAdder::addOutcome ao2 = addFR.addData("F34, Tokyo,2134, megacarrier");
	cout << ao2.status << "; " << ao2.message << endl;
	DataAdder::addOutcome ao3 = addFR.addData("F88, Pyong Yang, 0905, cargoCruISER");
	cout << ao3.status << "; " << ao3.message << endl;

	//search data
	DataDisplayer::searchOutcome so1 = displayFR.searchData("F88");
	int searchindex = so1.index;

	if (so1.status == "DATA_FOUND") { cout << "Search found, at index " << searchindex << ".\n"; }
	else if (so1.status == "DATA_NOT_FOUND") { cout << "Search not found.\n"; }

	//display data
	int index = 0; DataDisplayer::dataValues dv = displayFR.getDataValues(index);

	while (dv.status != "NO_DATA") {
		cout << "Index " << index << ": ";
		cout << "ID is " << dv.id << "; capacity is " << dv.extraVal2 << "; name is " << dv.extraVal1;
		cout << "; Destination is " << dv.destination << "; time is " << dv.time << "\n\n";
		dv = displayFR.getDataValues(++index); //increment index and then get the next data value
	}

	return 0;
}
*/
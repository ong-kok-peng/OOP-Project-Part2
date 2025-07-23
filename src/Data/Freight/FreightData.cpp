/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
#include <regex>
// imports for converting string to lowercase
#include <algorithm> // to use std::transform 
#include <cctype> // to use ::toupper and ::tolower
using namespace std;

#include "FreightData.h"

FreightData::FreightData() { id = ""; capacity = 0; }

TransportEntity::validationOutcome FreightData::setValues(string id, string dest, string time, string name) {
	validationOutcome vo;

	//set destination and time first
	TransportEntity::validationOutcome vo_destTime = TransportEntity::setValues(dest, time);
	if (!vo_destTime.validationPass) { vo.validationPass = false;  vo.message += vo_destTime.message; }

	//remove leading and trailing whitespace for the id and name
	id.erase(0, id.find_first_not_of(" \t\r\n")); id.erase(id.find_last_not_of(" \t\r\n") + 1);
	name.erase(0, name.find_first_not_of(" \t\r\n")); name.erase(name.find_last_not_of(" \t\r\n") + 1);

	//validate id as FXX i.e. F00 to F99
	regex idPattern(R"(^F\d\d$)");
	if (!regex_match(id, idPattern)) {
		vo.validationPass = false;
		vo.message += "ID ";
	}
	else { this->id = id; }

	//validate name
	transform(name.begin(), name.end(), name.begin(), ::tolower); // convert name value to lowercase

	if (name.compare("minimover") == 0) { capacity = 2; this->name = name;  }
	else if (name.compare("cargocruiser") == 0) { capacity = 6; this->name = name; }
	else if (name.compare("megacarrier") == 0) { capacity = 12; this->name = name; }
	else {
		vo.validationPass = false; vo.message += "Name ";
	}

	return vo;
}

std::string FreightData::getId() { return id; }

string FreightData::getName() { return name; }

int FreightData::getCapacity() { return capacity; }

/* test main code
int main() {
	FreightData freightData;
	TransportEntity::validationOutcome vo = freightData.setValues("F01", "HONOLULU", "1456", "cargoCruiser");
	if (vo.validationPass) {
		cout << "ID is " << freightData.getId() << "; capacity is " << freightData.getCapacity() << "; name is " << freightData.getName();
		cout << "; Destination is " << freightData.getDestination() << "; time is " << freightData.getTime() << endl;
	}
	else { cout << "Validation error(s) in: " << vo.message << endl; }

	return 0;
}
*/
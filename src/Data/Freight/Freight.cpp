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

#include "Freight.h"

Freight::Freight() { id = ""; capacity = 0; }

TransportEntity::validationOutcome Freight::setValues(string id, string dest, string time, string name) {
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

std::string Freight::getId() { return id; }

string Freight::getName() { return name; }

int Freight::getCapacity() { return capacity; }

/* test main code
int main() {
	Freight freight;
	TransportEntity::validationOutcome vo = freight.setValues("F01", "HONOLULU", "1456", "cargoCruiser");
	if (vo.validationPass) {
		cout << "ID is " << freight.getId() << "; capacity is " << freight.getCapacity() << "; name is " << freight.getCapacity();
		cout << "; Destination is " << freight.getDestination() << "; time is " << freight.getTime() << endl;
	}
	else { cout << "Validation error(s) in: " << vo.message << endl; }

	return 0;
}
*/
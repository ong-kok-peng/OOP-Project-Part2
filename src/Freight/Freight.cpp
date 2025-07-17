#include <iostream>
#include <string>
#include <regex>
// imports for converting string to lowercase
#include <algorithm> // to use std::transform 
#include <cctype> // to use ::toupper and ::tolower
using namespace std;

#include "Freight.h"

Freight::Freight() { id = ""; name = ""; capacity = 0; }

bool Freight::setId(string id) {
	//remove leading and trailing whitespace
	id.erase(0, id.find_first_not_of(" \t\r\n")); id.erase(id.find_last_not_of(" \t\r\n") + 1);

	//validate id as FXX i.e. F00 to F99
	regex idPattern(R"(^F\d\d$)");
	if (regex_match(id, idPattern)) {
		this->id = id;
		return true;
	}
	else {
		//error; ID must be in the form of FXX, where XX is a 2-digit number.
		return false;
	}
}

bool Freight::setName(string name) {
	// check the name of freight from user input
	// if its either minimover/cargocruiser/megacruiser, set the corresponding capacity value

	name.erase(0, name.find_first_not_of(" \t\r\n")); name.erase(name.find_last_not_of(" \t\r\n") + 1); //remove leading and trailing whitespace
	transform(name.begin(), name.end(), name.begin(), ::tolower); // convert name value to lowercase

	if (name.compare("minimover") == 0) { capacity = 2; this->name = name; return true; }
	else if (name.compare("cargocruiser") == 0) { capacity = 6; this->name = name; return true; }
	else if (name.compare("megacarrier") == 0) { capacity = 12; this->name = name; return true; }
	else { return false; } // value when validation fails
}

string Freight::getId() { return id; }

string Freight::getName() { return name; }

int Freight::getCapacity() { return capacity; }

/* test main code
int main() {
	Freight f("Singapore", "1230", "F05", "esgsehg");
	cout << f.getCapacity();

	return 0;
}
*/
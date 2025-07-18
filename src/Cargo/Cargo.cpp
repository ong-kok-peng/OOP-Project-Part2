/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
#include <regex>
using namespace std;

#include "Cargo.h"

Cargo::Cargo() { id = ""; quantity = 0; }

bool Cargo::setId(string id) {
	//remove leading and trailing whitespace
	id.erase(0, id.find_first_not_of(" \t\r\n")); id.erase(id.find_last_not_of(" \t\r\n") + 1);

	//validate id as CXX i.e. C00 to C99
	regex idPattern(R"(^C\d\d$)");
	if (regex_match(id, idPattern)) {
		this->id = id;
		return true;
	}
	else {
		//error; ID must be in the form of CXX, where XX is a 2-digit number.
		return false;
	}
}

bool Cargo::setQuantity(int quantity) {
	if (quantity > 0 && quantity <= 10) { this->quantity = quantity; return true; }
	else { return false; } // value when validation fails
}

std::string Cargo::getId() const {
    return id;
}

int Cargo::getQuantity() const {
    return quantity;
}

/* test main code
int main() {
	Cargo cargo;
	cargo.setTime("1240"); cargo.setQuantity(8);
	cout << cargo.getTime() << "\n";
	cout << cargo.getQuantity();

	return 0;
}
*/

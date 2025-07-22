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

TransportEntity::validationOutcome Cargo::setValues(string id, string dest, string time, string quantity) {
	validationOutcome vo;

	//set destination and time first
	TransportEntity::validationOutcome vo_destTime = TransportEntity::setValues(dest, time);
	if (!vo_destTime.validationPass) { vo.validationPass = false;  vo.message += vo_destTime.message; }

	//remove leading and trailing whitespace for the id and quantity
	id.erase(0, id.find_first_not_of(" \t\r\n")); id.erase(id.find_last_not_of(" \t\r\n") + 1);
	quantity.erase(0, quantity.find_first_not_of(" \t\r\n")); quantity.erase(quantity.find_last_not_of(" \t\r\n") + 1);

	//validate id as CXX i.e. C00 to C99
	regex idPattern(R"(^C\d\d$)");
	if (!regex_match(id, idPattern)) {
		vo.validationPass = false;
		vo.message += "ID ";
	}
	else { this->id = id; }

	//validate quantity
	try {
		int qty = stoi(quantity);
		if (qty > 0 && qty <= 10) { this->quantity = qty; }
		else { vo.validationPass = false; vo.message += "Quantity"; } // value when validation fails
	}
	catch (invalid_argument& e) { vo.validationPass = false; vo.message += "Quantity"; }

	return vo;
}

std::string Cargo::getId() {
	return id;
}

int Cargo::getQuantity() {
	return quantity;
}

/* test main code
int main() {
	Cargo cargo;
	TransportEntity::validationOutcome vo = cargo.setValues("D01", "HONOL54ULU", "1456", "6");
	if (vo.validationPass) {
		cout << "ID is " << cargo.getId() << "; quantity is " << cargo.getQuantity();
		cout << "; Destination is " << cargo.getDestination() << "; time is " << cargo.getTime() << endl;
	}
	else { cout << "Validation error(s) in: " << vo.message << endl; }

	return 0;
}
*/

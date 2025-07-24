/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#include <iostream>
#include <string>
#include <regex>
using namespace std;

#include "CargoData.h"

CargoData::CargoData() { id = ""; quantity = 0; }

TransportEntity::validationOutcome CargoData::setValues(string id, string dest, string time, string quantity) {
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

std::string CargoData::getId() {
	return id;
}

int CargoData::getQuantity() {
	return quantity;
}

/* test main code
int main() {
	CargoData cargo;
	TransportEntity::validationOutcome vo = cargo.setValues("C01", "HONOLULU", "1456", "6");
	if (vo.validationPass) {
		cout << "ID is " << cargo.getId() << "; quantity is " << cargo.getQuantity();
		cout << "; Destination is " << cargo.getDestination() << "; time is " << cargo.getTime() << endl;
	}
	else { cout << "Validation error(s) in: " << vo.message << endl; }

	return 0;
}
*/

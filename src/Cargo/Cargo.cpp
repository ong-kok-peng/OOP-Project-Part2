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

string Cargo::getId() { return id; }

int Cargo::getQuantity() { return quantity; }

/* test main code
int main() {
	Cargo c("Singapore", "2300", "F05", 6);
	cout << c.getTime();

	return 0;
}
*/

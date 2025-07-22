/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
#include <regex>
using namespace std;

#include "TransportEntity.h"

TransportEntity::TransportEntity() { destination = ""; time = ""; }

TransportEntity::validationOutcome TransportEntity::setValues(string dest, string time) {
	validationOutcome vo;

	//remove leading and trailing whitespace for the values
	dest.erase(0, dest.find_first_not_of(" \t\r\n")); dest.erase(dest.find_last_not_of(" \t\r\n") + 1);
	time.erase(0, time.find_first_not_of(" \t\r\n")); time.erase(time.find_last_not_of(" \t\r\n") + 1);

	//validate values
	regex destPattern(R"(^[a-zA-Z ]+$)");
	if (!regex_match(dest, destPattern)) {
		
		vo.validationPass = false;
		vo.message += "Destination ";
	}
	else { destination = dest; }

	regex timePattern(R"(([01]{1}[0-9]|2[0-3])[0-5][0-9])");
	if (!regex_match(time, timePattern)) {
		vo.validationPass = false;
		vo.message += "Time ";
	}
	else { this->time = time; }

	return vo;
}

string TransportEntity::getDestination() { return destination; }

string TransportEntity::getTime() { return time; }

/* test main code
int main() {
	TransportEntity te;
	TransportEntity::validationOutcome vo = te.setValues("honolulu", "2345");
	if (vo.validationPass) {
		cout << "Destination is " << te.getDestination() << "; time is " << te.getTime() << endl;
	}
	else { cout << "Validation error(s) in: " << vo.message << endl; }
	return 0;
}
*/
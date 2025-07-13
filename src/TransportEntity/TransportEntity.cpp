#include <iostream>
#include <string>
#include <regex>
using namespace std;

#include "TransportEntity.h"

TransportEntity::TransportEntity() { destination = ""; time = ""; }

bool TransportEntity::setDestination(string destination) {
	//remove leading and trailing whitespace for the value
	destination.erase(0, destination.find_first_not_of(" \t\r\n")); destination.erase(destination.find_last_not_of(" \t\r\n") + 1);

	regex destPattern(R"(^[a-zA-Z ]+$)");
	if (regex_match(destination, destPattern)) {
		this->destination = destination;
		return true;
	}
	else {
		//error: Destination must be a alphabetical with or w/o spaces string!
		return false;
	}
}

bool TransportEntity::setTime(string time) {
	//remove leading and trailing whitespace
	time.erase(0, time.find_first_not_of(" \t\r\n")); time.erase(time.find_last_not_of(" \t\r\n") + 1);

	//validate time as 0000 to 2359
	regex timePattern(R"(([01]{1}[0-9]|2[0-3])[0-5][0-9])");
	if (regex_match(time, timePattern)) {
		this->time = time;
		return true;
	}
	else {
		//error: Time must be in the form of 24 hour format i.e. 1235 or 0912.
		return false;
	}
}

string TransportEntity::getDestination() { return destination; }

string TransportEntity::getTime() { return time; }
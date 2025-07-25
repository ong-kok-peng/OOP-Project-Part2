/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "TxtFormatStrategy.h"

string TxtFormatStrategy::createFileExtension() { return ".txt"; }

string TxtFormatStrategy::createFileHeader(vector<string> headerValues) {
	string line = "";
	for (int i = 0; i < headerValues.size(); i++) {
		//print a tab delimeter until the last header value
		if (i != headerValues.size() - 1) {
			line += headerValues[i] + "\t";
		}
		else {
			line += headerValues[i] + "\n";
		}
	}
	return line;
}

string TxtFormatStrategy::createFileLine(DataDisplayer::dataValues& dv) {
	string line = "";

	line += dv.id + "\t"; //write ID

	if (dv.destination.length() <= 7) { line += dv.destination + "\t\t"; } //write destination; if too short put 2 tab characters
	else { line += dv.destination + "\t"; }

	line += dv.time + "\t"; line += dv.extraVal1 + "\n"; //write time and name, where name is under extra value 1

	return line;
}
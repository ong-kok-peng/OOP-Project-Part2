/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "CsvFormatStrategy.h"

string CsvFormatStrategy::createFileExtension() { return ".csv"; }

string CsvFormatStrategy::createFileHeader(vector<string> headerValues) {
	string line = "";
	for (int i = 0; i < headerValues.size(); i++) {
		//print a comma delimeter until the last header value
		if (i != headerValues.size() - 1) {
			line += headerValues[i] + ",";
		}
		else {
			line += headerValues[i] + "\n";
		}
	}
	return line;
}

string CsvFormatStrategy::createFileLine(DataDisplayer::dataValues& dv) {
	string line = dv.id + "," + dv.destination + "," + dv.time + "," + dv.extraVal1 + "\n"; //name is under extra value 1
	return line;
}
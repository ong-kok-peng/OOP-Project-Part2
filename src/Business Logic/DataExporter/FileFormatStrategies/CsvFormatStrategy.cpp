/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "CsvFormatStrategy.h"

string CsvFormatStrategy::createFileExtension() { return ".csv"; }

string CsvFormatStrategy::createFileHeader_Freight() {
	return "ID,Destination,Time,Freight Name\n";
}

string CsvFormatStrategy::createFileLine_Freight(DataDisplayer::dataValues& dv) {
	string line = dv.id + "," + dv.destination + "," + dv.time + "," + dv.extraVal1 + "\n"; //name is under extra value 1
	return line;
}

string CsvFormatStrategy::createFileHeader_Cargo() {
	return "ID,Destination,Time,Cargo Quantity\n";
}

string CsvFormatStrategy::createFileLine_Cargo(DataDisplayer::dataValues& dv) {
	string line = dv.id + "," + dv.destination + "," + dv.time + "," + dv.extraVal1 + "\n"; //quantity is under extra value 1
	return line;
}
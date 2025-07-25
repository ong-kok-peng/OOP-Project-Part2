/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "FreightDataExporter.h"

FreightDataExporter::FreightDataExporter(FreightDataDisplayer& displayFR) : displayFR{ displayFR } {}

DataExporter::exportOutcome FreightDataExporter::setExportFileFormat(string fileFormat) {
	exportOutcome eo; 

	if (fileFormat == "TXT") { fileFormatStrategy = new TxtFormatStrategy(); eo.status = "SUCCESS"; eo.message = "File will be in ." + fileFormat + "."; }
	else if (fileFormat == "CSV") { fileFormatStrategy = new CsvFormatStrategy(); eo.status = "SUCCESS"; eo.message = "File will be in ." + fileFormat + "."; }
	else { eo.status = "ERROR"; eo.message = "Invalid file format selected"; }
	return eo;
}

DataExporter::exportOutcome FreightDataExporter::exportToFile(string input) {
	exportOutcome eo;

	if (input == "CANCEL") { eo.status = "CANCELLED"; eo.message = "Exporting data is cancelled."; return eo; }

	//check if file format is selected
	if (fileFormatStrategy == nullptr) { eo.status = "ERROR"; eo.message = "Export file format is not set"; return eo; }

	string filename = input + fileFormatStrategy->createFileExtension(); //add file extension to the input file name

	FileWriter writer(filename, false);
	if (!writer.isFileOpened()) {
		eo.status = "ERROR"; eo.message = "\"" + filename + "\" file path is invalid."; return eo;
	}

	//from this point onwards, eo.message is a multiline output

	eo.status = "SUCCESS";
	eo.message += "Exporting freight data to file \"" + filename + "\"...\n";

	string header = fileFormatStrategy->createFileHeader({ "ID", "Destination", "Time", "Freight Name" }); //create file header based on file format
	writer.writeLine(header); //write header as line 1

	//write line by line to the file
	int index = 0; DataDisplayer::dataValues dv = displayFR.getDataValues(index);

	while (dv.status != "NO_DATA") {
		writer.writeLine(fileFormatStrategy->createFileLine(dv)); //write lines based on file format
		dv = displayFR.getDataValues(++index); //increment index and then get the next data value
	}

	writer.closeFile();

	eo.message += "Successfully exported " + to_string(index) + " records successfully!";
	return eo;
}

/* main test code
#include "../DataAdder/FreightDataAdder.h"

int main() {
	FreightDataPool fr;
	FreightDataAdder addFR(fr); FreightDataDisplayer displayFR(fr); FreightDataExporter exportFR(displayFR);

	//add individual data
	DataAdder::addOutcome ao1 = addFR.addData("F45,Honolulu,1256,megaCarrier");
	cout << ao1.status << "; " << ao1.message << endl;
	DataAdder::addOutcome ao2 = addFR.addData("F34, Tokyo,2134, megacarrier");
	cout << ao2.status << "; " << ao2.message << endl;
	DataAdder::addOutcome ao3 = addFR.addData("F88, Pyong Yang, 0905, cargoCruISER");
	cout << ao3.status << "; " << ao3.message << endl;

	//display data
	int index = 0; DataDisplayer::dataValues dv = displayFR.getDataValues(index);

	while (dv.status != "NO_DATA") {
		cout << "Index " << index << ": ";
		cout << "ID is " << dv.id << "; capacity is " << dv.extraVal2 << "; name is " << dv.extraVal1;
		cout << "; Destination is " << dv.destination << "; time is " << dv.time << "\n\n";
		dv = displayFR.getDataValues(++index); //increment index and then get the next data value
	}

	//export data to file
	string filename = "helloworld3";

	DataExporter::exportOutcome setFormatO = exportFR.setExportFileFormat("TXT");
	if (setFormatO.status == "SUCCESS") {
		DataExporter::exportOutcome eo = exportFR.exportToFile(filename);
		cout << eo.status << "; " << eo.message << "\n";
	}
	else if (setFormatO.status == "ERROR") {
		cout << setFormatO.message << endl;
	}

	

	return 0;
}
*/
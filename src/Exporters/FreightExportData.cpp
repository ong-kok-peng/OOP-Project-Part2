/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 18/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "FreightExportData.h"

FreightExportData::FreightExportData(IReadFreightRecords& readFR) : readFR{ readFR } {}

void FreightExportData::exportRecords() {
	cout << "------ Exporting Freight Records ------\n\n";

	if (readFR.getRecordsSize() == 0) {
		cout << "There are no records. Add a new record or import from a file.\n";
		return;
	}
    
}
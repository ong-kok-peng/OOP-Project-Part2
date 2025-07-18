/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 18/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "CargoExportData.h"

CargoExportData::CargoExportData(IReadCargoRecords& readCR) : readCR{ readCR } {}

void CargoExportData::exportRecords() {
    cout << "------ Exporting Cargo Records ------\n\n";

    if (readCR.getRecordsSize() == 0) {
        cout << "There are no records. Add a new record or import from a file.\n";
        return;
    }
    
}

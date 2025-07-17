#include "FileWriter.h"
#include <fstream>
/*
Created by: Chia Boon Pin (2403120)
Date: 17/7/2025
*/

FileWriter::FileWriter() {}

FileWriter::~FileWriter() {}

bool FileWriter::writeToFile(const std::string& filename, const std::string& data, bool append) {
    std::ofstream outFile;

    if (append)
        outFile.open(filename, std::ios::app);
    else
        outFile.open(filename, std::ios::trunc);

    if (!outFile.is_open()) {
        return false;
    }

    outFile << data << "\n";
    outFile.close();
    return true;
}

bool FileWriter::writeCargoExportData(/* const CargoExportData& data */) {
    // TODO: Implement logic to convert CargoExportData to string lines
    // and call writeToFile for each record
    // Example:
    // for (int i = 0; i < data.getSize(); ++i) {
    //     std::string csvLine = data.getRecord(i).toCSV(); // value to input
    //     writeToFile("cargo_output.csv", csvLine, true);  // filename = value to input
    // }
    return false; // stub
}

bool FileWriter::writeFreightExportData(/* const FreightExportData& data */) {
    // TODO: Implement logic to convert FreightExportData to string lines
    // and call writeToFile for each record
    return false; // stub
}

bool FileWriter::writeSchedulerExportData(/* const SchedulerExportData& data */) {
    // TODO: Implement logic to convert SchedulerExportData to string lines
    // and call writeToFile for each record
    return false; // stub
}
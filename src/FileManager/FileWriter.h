#pragma once
#include <string>
/*
Created by: Chia Boon Pin (2403120)
Date: 17/7/2025
*/

class FileWriter {
public:
    FileWriter();
    ~FileWriter();

    bool writeToFile(const std::string& filename, const std::string& data, bool append = true);

    // Placeholder for writing cargo export data
    bool writeCargoExportData(/* const CargoExportData& data */); // variable to input

    // Placeholder for writing freight export data
    bool writeFreightExportData(/* const FreightExportData& data */); // variable to input

    // Placeholder for writing scheduler export data
    bool writeSchedulerExportData(/* const SchedulerExportData& data */); // variable to input
};
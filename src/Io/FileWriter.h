#pragma once
#include <string>

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
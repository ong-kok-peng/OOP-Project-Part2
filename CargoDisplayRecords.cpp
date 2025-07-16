#include "CargoDisplayRecords.h"
#include "FileWriter.h"
#include <iostream>
#include <iomanip>

CargoDisplayRecords::CargoDisplayRecords(const CargoRecords& records)
    : cargoRecords(records) {}

void CargoDisplayRecords::displayRecords() const {
    auto all = cargoRecords.getAllRecords();
    std::cout << std::left
              << std::setw(6) << "Idx"
              << std::setw(10) << "CargoID"
              << std::setw(12) << "FreightID"
              << std::setw(15) << "Destination"
              << std::setw(10) << "Time"
              << std::endl;
    for (int i = 0; i < static_cast<int>(all.size()); ++i) {
        const auto& c = all[i];
        std::cout << std::left
                  << std::setw(6) << i
                  << std::setw(10) << c.getId()
                  << std::setw(12) << c.getFreightId()
                  << std::setw(15) << c.getDestination()
                  << std::setw(10) << c.getTime()
                  << std::endl;
    }
}

bool CargoDisplayRecords::saveRecordsToFile(const std::string& fileName) const {
    FileWriter writer;
    std::vector<std::string> lines;
    auto all = cargoRecords.getAllRecords();
    for (const auto& c : all) {
        lines.push_back(c.getId() + "," + c.getFreightId() + "," + c.getDestination() + "," + c.getTime());
    }
    return writer.writeFile(fileName, lines);
}
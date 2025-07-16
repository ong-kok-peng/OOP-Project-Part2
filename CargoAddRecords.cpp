#include "CargoAddRecords.h"
#include "FileReader.h"

CargoAddRecords::CargoAddRecords(CargoRecords& records)
    : cargoRecords(records) {}

bool CargoAddRecords::addRecordsFromFile(const std::string& fileName) {
    FileReader reader;
    std::vector<std::string> lines;
    if (!reader.readFile(fileName, lines)) return false;
    for (const auto& line : lines) {
        auto fields = reader.split(line, ',');
        if (fields.size() < 4) continue; // invalid row
        Cargo c(fields[0], fields[1], fields[2], fields[3]);
        cargoRecords.addCargoRecord(c);
    }
    return true;
}

bool CargoAddRecords::addRecord(const Cargo& record) {
    // check duplicate
    auto all = cargoRecords.getAllRecords();
    for (auto& existing : all) {
        if (existing.getId() == record.getId()) return false;
    }
    cargoRecords.addCargoRecord(record);
    return true;
}

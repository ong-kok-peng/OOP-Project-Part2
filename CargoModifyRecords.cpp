#include "CargoModifyRecords.h"

CargoModifyRecords::CargoModifyRecords(CargoRecords& records)
    : cargoRecords(records) {}

bool CargoModifyRecords::editRecord(int index, const Cargo& newRecord) {
    auto all = cargoRecords.getAllRecords();
    if (index < 0 || index >= static_cast<int>(all.size())) return false;
    cargoRecords.updateCargoRecord(index, newRecord);
    return true;
}

bool CargoModifyRecords::deleteRecord(int index) {
    auto all = cargoRecords.getAllRecords();
    if (index < 0 || index >= static_cast<int>(all.size())) return false;
    cargoRecords.removeCargoRecord(index);
    return true;
}
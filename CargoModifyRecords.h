#pragma once
#include "IModifyRecords.h"
#include "CargoRecords.h"

class CargoModifyRecords : public IModifyRecords {
public:
    CargoModifyRecords(CargoRecords& records);
    bool editRecord(int index, const Cargo& newRecord) override;
    bool deleteRecord(int index) override;
private:
    CargoRecords& cargoRecords;
};
#pragma once
#include "IDisplayRecords.h"
#include "CargoRecords.h"

class CargoDisplayRecords : public IDisplayRecords {
public:
    CargoDisplayRecords(const CargoRecords& records);
    void displayRecords() const override;
    bool saveRecordsToFile(const std::string& fileName) const override;
private:
    const CargoRecords& cargoRecords;
};

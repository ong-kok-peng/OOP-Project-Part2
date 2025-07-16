#pragma once

#ifndef CARGO_MODIFY_RECORDS_H
#define CARGO_MODIFY_RECORDS_H

#include "IModifyRecords.h"
#include "../Cargo/CargoRecords.h"

class CargoModifyRecords : public IModifyRecords {
private:
    CargoRecords& cargoRecords;

public:
    CargoModifyRecords(CargoRecords& cr);
    void modifyRecord(int index) override;
    void deleteRecord(int index) override;
};

#endif

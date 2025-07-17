#pragma once

#ifndef CARGO_MODIFY_RECORDS_H
#define CARGO_MODIFY_RECORDS_H

#include "IModifyRecords.h"
#include "../Cargo/CargoRecords.h"

class CargoModifyRecords : public IModifyRecords {
private:
    CargoRecords& cr;

public:
    CargoModifyRecords(CargoRecords& cr);
    void editRecord() override;
    void deleteRecord() override;
};

#endif




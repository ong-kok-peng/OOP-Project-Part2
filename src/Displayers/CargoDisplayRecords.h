#pragma once

#ifndef CARGO_DISPLAY_RECORDS_H
#define CARGO_DISPLAY_RECORDS_H

#include "IDisplayRecords.h"
#include "../Cargo/IReadCargoRecords.h"

class CargoDisplayRecords : public IDisplayRecords {
private:
    IReadCargoRecords* readCR;

public:
    CargoDisplayRecords(IReadCargoRecords* rcr);
    void displayRecord() override;
    void saveRecordsToFile() override;
};

#endif

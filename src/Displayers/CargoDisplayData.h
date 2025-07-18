/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#pragma once

#ifndef CARGO_DISPLAY_DATA_H
#define CARGO_DISPLAY_DATA_H

#include "IDisplayData.h"
#include "../Cargo/IReadCargoRecords.h"

class CargoDisplayData : public IDisplayData {
private:
    IReadCargoRecords& readCR;

public:
    CargoDisplayData(IReadCargoRecords& readCR);
    void displayRecords() override;
};

#endif

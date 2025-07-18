/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 18/7/2025
*/

#pragma once

#ifndef CARGO_EXPORT_DATA_H
#define CARGO_EXPORT_DATA_H

#include "IExportData.h"
#include "../Cargo/IReadCargoRecords.h"

class CargoExportData : public IExportData {
private:
    IReadCargoRecords& readCR;

public:
    CargoExportData(IReadCargoRecords& readCR);
    void exportRecords() override;
};

#endif#pragma once

#pragma once
#pragma once

#ifndef CARGO_ADD_RECORDS_H
#define CARGO_ADD_RECORDS_H

#include "IAddRecords.h"
#include "../Cargo/CargoRecords.h"

class CargoAddRecords : public IAddRecords {
private:
	CargoRecords& fr;

public:
	CargoAddRecords(CargoRecords &cr);
	void addRecord() override;
	void addRecordsFromFile() override;
};

#endif

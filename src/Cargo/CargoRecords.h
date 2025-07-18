/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef CARGO_RECORDS_H
#define CARGO_RECORDS_H

#include <vector>
#include "IReadCargoRecords.h"
#include "Cargo.h"


class CargoRecords : public IReadCargoRecords {
private:
	vector<Cargo> records;

public:
	CargoRecords();
	int getRecordsSize() override;
	Cargo getCargo(int index) override;
	void sortCargoByTime() override;
	void sortCargoByQuantity() override;

	int getRecordIndex(string id);
	void addCargo(Cargo c);
	void deleteCargo(int index);
	void editCargo(int index, Cargo c);
	void clearRecords();
};

#endif

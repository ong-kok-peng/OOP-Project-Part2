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
	struct recordOutcome { string status = ""; string message = ""; };
	CargoRecords();
	int getRecordsSize() override;
	Cargo getCargo(int index) override;
	void sortCargoByTime() override;
	void sortCargoByQuantity() override;

	int getRecordIndex(string id);
	recordOutcome addCargo(string userInput);
	recordOutcome appendCargo(int addQuantity, int index, Cargo currentRecord);
	recordOutcome deleteCargo(int index, char deleteYesNo);
	recordOutcome removeCargo(int removeQuantity, int index, Cargo currentRecord);
	recordOutcome editCargo(string userInput, int index, Cargo currentRecord);
	void clearRecords();
};

#endif

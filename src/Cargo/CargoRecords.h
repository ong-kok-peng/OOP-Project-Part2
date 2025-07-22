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
	struct modifyRecordOutcome { string status = ""; string message = ""; };
	CargoRecords();
	int getRecordsSize() override;
	Cargo getCargoByIndex(int index) override;
	getRecordOutcome getCargoById(string id) override;

	void sortCargoByTime() override;
	void sortCargoByQuantity() override;

	modifyRecordOutcome addCargo(string userInput);
	modifyRecordOutcome appendCargo(int addQuantity, int index, Cargo currentRecord);
	modifyRecordOutcome deleteCargo(int index, char deleteYesNo);
	modifyRecordOutcome removeCargo(int removeQuantity, int index, Cargo currentRecord);
	modifyRecordOutcome editCargo(string userInput, int index, Cargo currentRecord);
	void clearRecords();
};

#endif

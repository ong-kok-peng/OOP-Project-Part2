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
	bool appendCargo(int index, int quantity);
	void deleteCargo(int index);
	bool removeCargo(int index, int quantity);
	void editCargo(int index, Cargo c);
	void editCargoRecord(int index, Cargo c);
	void deleteCargoRecord(int index);
	std::vector<Cargo> getAllRecords() const override;

};

#endif

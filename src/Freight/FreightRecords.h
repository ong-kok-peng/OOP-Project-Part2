#pragma once

#ifndef FREIGHT_RECORDS_H
#define FREIGHT_RECORDS_H

#include <vector>
#include "IReadFreightRecords.h"
#include "Freight.h"

class FreightRecords : public IReadFreightRecords {
private:
	vector<Freight> records;

public:
	FreightRecords();
	int getRecordsSize() override;
	Freight getFreight(int index) override;
	void sortFreightByTime() override;
	void sortFreightByQuantity() override;

	int getRecordIndex(string id);
	void addFreight(Freight f);
	void deleteFreight(int index);
	void editFreight(int index, Freight f);
};

#endif

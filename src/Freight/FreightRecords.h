/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

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
	struct recordOutcome { string status = ""; string message = ""; };
	FreightRecords();
	int getRecordsSize() override;
	Freight getFreight(int index) override;
	void sortFreightByTime() override;
	void sortFreightByQuantity() override;

	int getRecordIndex(string id);
	recordOutcome addFreight(string userInput);
	recordOutcome deleteFreight(int index, char deleteYesNo);
	recordOutcome editFreight(string userInput, int index, Freight currentRecord);
	void clearRecords();
};

#endif

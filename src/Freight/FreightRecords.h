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
	struct modifyRecordOutcome { string status = ""; string message = ""; };
	FreightRecords();
	int getRecordsSize() override;
	Freight getFreightByIndex(int index) override;
	getRecordOutcome getFreightById(string id) override;

	void sortFreightByTime() override;
	void sortFreightByCapacity() override;

	modifyRecordOutcome addFreight(string userInput);
	modifyRecordOutcome deleteFreight(int index, char deleteYesNo);
	modifyRecordOutcome editFreight(string userInput, int index, Freight currentRecord);
	void clearRecords();
};

#endif

/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef I_READ_CARGO_RECORDS_H
#define I_READ_CARGO_RECORDS_H

#include "Cargo.h"
#include <vector>

class IReadCargoRecords {
public:
	struct getRecordOutcome { string status = ""; int index = -1; Cargo currentRecord; };
	virtual int getRecordsSize() = 0;
	virtual Cargo getCargoByIndex(int index) = 0;
	virtual getRecordOutcome getCargoById(string id) = 0;
	virtual void sortCargoByTime() = 0;
	virtual void sortCargoByQuantity() = 0;
};

#endif

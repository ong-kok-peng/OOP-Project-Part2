#pragma once

#ifndef FREIGHT_ADD_RECORDS_H
#define FREIGHT_ADD_RECORDS_H

#include "IAddRecords.h"
#include "../Freight/FreightRecords.h"

class FreightAddRecords : public IAddRecords {
private:
	FreightRecords& fr;

public:
	FreightAddRecords(FreightRecords& fr);
	void addRecord() override;
	void addRecordsFromFile() override;
};

#endif

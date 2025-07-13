#pragma once

#ifndef I_READ_FREIGHT_RECORDS_H
#define I_READ_FREIGHT_RECORDS_H

#include "Freight.h"

class IReadFreightRecords{
public:
	virtual int getRecordsSize() = 0;
	virtual Freight getFreight(int index) = 0;
	virtual void sortFreightByTime() = 0;
	virtual void sortFreightByQuantity() = 0;
};

#endif
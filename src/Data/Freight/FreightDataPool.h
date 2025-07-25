/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_DATAPOOL_H
#define FREIGHT_DATAPOOL_H

#include <vector>
#include "FreightData.h"

class FreightDataPool  {
private:
	vector<FreightData> freights;

public:
	FreightDataPool();
	void addFreight(FreightData f);
	void editFreight(int index, FreightData f);
	void deleteFreight(int index);
	vector<int> getFreightIndexsByValue(string value);
	FreightData* getFreightByIndex(int index);
	void clearAllFreight();
	void sortByTime();
	void sortByCapacity();
};

#endif

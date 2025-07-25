/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_DATAPOOL_H
#define FREIGHT_DATAPOOL_H

#include <vector>
#include "I_AddFreightDataPool.h"
#include "I_ModifyFreightDataPool.h"
#include "I_DisplayFreightDataPool.h"
#include "I_SortFreightDataPool.h"

class FreightDataPool : public I_AddFreightDataPool, public I_ModifyFreightDataPool, 
						public I_DisplayFreightDataPool, public I_SortFreightDataPool {
private:
	vector<FreightData> freights;

public:
	FreightDataPool();
	void addFreight(FreightData f) override;
	void editFreight(int index, FreightData f) override;
	void deleteFreight(int index) override;
	vector<int> getFreightIndexsByValue(string value) override;
	FreightData* getFreightByIndex(int index) override;
	void clearAllFreight() override;
	void sortByTime() override;
	void sortByCapacity() override;
};

#endif

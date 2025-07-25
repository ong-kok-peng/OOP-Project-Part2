/*
Created by: Ong Kok Peng (2403435)
Date: 17/7/2025
*/

#pragma once

#include <vector>
#include <string>
#include "FreightData.h"

#ifndef I_ADDFREIGHT_DATAPOOL_H
#define I_ADDFREIGHT_DATAPOOL_H

class I_AddFreightDataPool {
public:
	virtual void addFreight(FreightData f) = 0;
	virtual void clearAllFreight() = 0;
	virtual std::vector<int> getFreightIndexsByValue(std::string value) = 0;
};

#endif
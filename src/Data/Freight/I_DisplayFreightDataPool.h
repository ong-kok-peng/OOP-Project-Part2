/*
Created by: Ong Kok Peng (2403435)
Date: 17/7/2025
*/

#pragma once

#include <string>
#include <vector>
#include "FreightData.h"

#ifndef I_DISPLAYFREIGHT_DATAPOOL_H
#define I_DISPLAYFREIGHT_DATAPOOL_H

class I_DisplayFreightDataPool {
public:
	virtual std::vector<int> getFreightIndexsByValue(std::string value) = 0;
	virtual FreightData* getFreightByIndex(int index) = 0;
};

#endif
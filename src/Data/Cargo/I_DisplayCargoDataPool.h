/*
Created by: Ong Kok Peng (2403435)
Date: 17/7/2025
*/

#pragma once

#include <string>
#include <vector>
#include "CargoData.h"

#ifndef I_DISPLAYCARGO_DATAPOOL_H
#define I_DISPLAYCARGO_DATAPOOL_H

class I_DisplayCargoDataPool {
public:
	virtual std::vector<int> getCargoIndexsByValue(std::string value) = 0;
	virtual CargoData* getCargoByIndex(int index) = 0;
};

#endif
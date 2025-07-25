/*
Created by: Ong Kok Peng (2403435)
Date: 17/7/2025
*/

#pragma once

#include <vector>
#include <string>
#include "CargoData.h"

#ifndef I_ADDCARGO_DATAPOOL_H
#define I_ADDCARGO_DATAPOOL_H

class I_AddCargoDataPool {
public:
	virtual void addCargo(CargoData f) = 0;
	virtual void clearAllCargo() = 0;
	virtual std::vector<int> getCargoIndexsByValue(std::string value) = 0;
};

#endif
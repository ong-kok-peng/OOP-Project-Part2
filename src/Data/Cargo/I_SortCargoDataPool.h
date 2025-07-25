/*
Created by: Ong Kok Peng (2403435)
Date: 17/7/2025
*/

#pragma once

#include "CargoData.h"

#ifndef I_SORTCARGO_DATAPOOL_H
#define I_SORTCARGO_DATAPOOL_H

class I_SortCargoDataPool {
public:
	virtual void sortByTime() = 0;
	virtual void sortByQuantity() = 0;
};

#endif
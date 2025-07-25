/*
Created by: Ong Kok Peng (2403435)
Date: 17/7/2025
*/

#pragma once

#include "FreightData.h"

#ifndef I_SORTFREIGHT_DATAPOOL_H
#define I_SORTFREIGHT_DATAPOOL_H

class I_SortFreightDataPool {
public:
	virtual void sortByTime() = 0;
	virtual void sortByCapacity() = 0;
};

#endif
/*
Created by: Ong Kok Peng (2403435)
Date: 17/7/2025
*/

#pragma once

#include "FreightData.h"

#ifndef I_MODIFYFREIGHT_DATAPOOL_H
#define I_MODIFYFREIGHT_DATAPOOL_H

class I_ModifyFreightDataPool {
public:
	virtual void editFreight(int index, FreightData f) = 0;
	virtual void deleteFreight(int index) = 0;
	virtual FreightData* getFreightByIndex(int index) = 0;
};

#endif
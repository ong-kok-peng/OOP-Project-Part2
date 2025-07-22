/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#pragma once

#ifndef I_SCHEDULE_BY_TIME_H
#define I_SCHEDULE_BY_TIME_H

#include <vector>
#include "ScheduleStrategies.h"

class ScheduleByTime : public ScheduleStrategies {
private:
	int freightIndex;
	int cargoIndex;
	int cumulatedCapacity;
	int cumulatedQuantity;
	vector<Freight> matchedFreightsBlk;
	vector<Cargo> matchedCargosBlk;
public:
	ScheduleByTime();
	scheduleMatchUpdate matchFreightCargo(Freight f, Cargo c) override;
};

#endif


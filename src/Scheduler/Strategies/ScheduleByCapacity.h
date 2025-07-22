/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#pragma once

#ifndef I_SCHEDULE_BY_CAPACITY_H
#define I_SCHEDULE_BY_CAPACITY_H

#include <vector>
#include "ScheduleStrategies.h"

class ScheduleByCapacity : public ScheduleStrategies {
private:
	int freightIndex;
	int cargoIndex;
	int cumulatedCapacity;
	int cumulatedQuantity;
	vector<Freight> matchedFreightsBlk;
	vector<Cargo> matchedCargosBlk;

	int cargoIndxStart = 0; bool loopCargos = false; bool cumulatedCargoFull = false; string matchedDest = "";

public:
	ScheduleByCapacity();
	scheduleMatchUpdate matchFreightCargo(Freight f, Cargo c) override;
};

#endif

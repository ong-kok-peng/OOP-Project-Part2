/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#pragma once

#ifndef SCHEDULE_BYCAPACITY_H
#define SCHEDULE_BYCAPACITY_H

#include "SchedulerStrategies.h"

class ScheduleByCapacity : public SchedulerStrategies {
private:
	string name;
public:
	ScheduleByCapacity();
	string getName() override;
	void sortDataPools(I_SortFreightDataPool& sfp, I_SortCargoDataPool& scp) override;
	string matchFreightCargo(string freightDest, string freightTime, string cargoDest, string cargoTime) override;
};

#endif

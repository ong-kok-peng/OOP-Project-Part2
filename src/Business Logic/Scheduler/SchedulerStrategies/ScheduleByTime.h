/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#pragma once

#ifndef SCHEDULEBY_TIME_H
#define SCHEDULEBY_TIME_H

#include "SchedulerStrategies.h"

class ScheduleByTime : public SchedulerStrategies {
private:
	string name;
public:
	ScheduleByTime();
	string getName() override;
	void sortDataPools(I_SortFreightDataPool& sfp, I_SortCargoDataPool& scp) override;
	string matchFreightCargo(string freightDest, string freightTime, string cargoDest, string cargoTime) override;
};

#endif

/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#pragma once

#ifndef SCHEDULER_STRATEGIES_H
#define SCHEDULER_STRATEGIES_H

#include "../../../Data/Freight/I_SortFreightDataPool.h"
#include "../../../Data/Cargo/I_SortCargoDataPool.h"

class SchedulerStrategies {
public:
	virtual string getName() = 0;
	virtual void sortDataPools(I_SortFreightDataPool& sfp, I_SortCargoDataPool& scp) = 0;
	string compareFreightCargoTime(string freightTime, string cargoTime);
	virtual string matchFreightCargo(string freightDest, string freightTime, string cargoDest, string cargoTime) = 0;
};

#endif
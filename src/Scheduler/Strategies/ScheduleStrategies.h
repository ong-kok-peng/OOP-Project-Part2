/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#pragma once

#include "../../Freight/Freight.h"
#include "../../Cargo/Cargo.h"
#include "../../Freight/IReadFreightRecords.h"
#include "../../Cargo/IReadCargoRecords.h"
#include "../ScheduleSlot.h"

#ifndef SCHEDULE_STRATEGIES_H
#define SCHEDULE_STRATEGIES_H

class ScheduleStrategies {
public:
	string name = "";
	struct scheduleMatchUpdate { string schedulerStatus = ""; int freightIndex = 0; int cargoIndex = 0; bool isSlotCreated = false; ScheduleSlot* newSlot = nullptr; };
	string compareTimeFromRecords(string freightTime, string cargoTime);
	virtual scheduleMatchUpdate matchFreightCargo(Freight f, Cargo c) = 0;
};

#endif
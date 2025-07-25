/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#pragma once

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../../Data/Freight/I_DisplayFreightDataPool.h"
#include "../../Data/Freight/I_SortFreightDataPool.h"
#include "../../Data/Cargo/I_DisplayCargoDataPool.h"
#include "../../Data/Cargo/I_SortCargoDataPool.h"

#include "./SchedulerStrategies/SchedulerStrategies.h"
#include "./SchedulerStrategies/ScheduleByCapacity.h"
#include "./SchedulerStrategies/ScheduleByTime.h"

class Scheduler {
private:
	I_DisplayCargoDataPool& displayCP;
	I_SortCargoDataPool& sortCP;

	I_DisplayFreightDataPool& displayFP;
	I_SortFreightDataPool& sortFP;

	SchedulerStrategies* scheduleStrategy = nullptr;

public:
	struct schedulerOutcome { string status = ""; string message = ""; };

	Scheduler(I_DisplayFreightDataPool& dfp, I_SortFreightDataPool& sfp,
		I_DisplayCargoDataPool& dcp, I_SortCargoDataPool& scp);

	schedulerOutcome setSchedulerOption(string option);
	schedulerOutcome getSchedulerOption();
	schedulerOutcome runScheduler();
};

#endif

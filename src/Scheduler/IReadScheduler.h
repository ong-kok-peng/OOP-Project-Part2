/*
Created by: Zhang Jiahua (2402050)
Date: 19/7/2025
*/

#pragma once

#ifndef I_READ_SCHEDULER_H
#define I_READ_SCHEDULER_H

#include "ScheduleSlot.h"

class IReadScheduler {
public:
	virtual int getSlotsSize() = 0;
	virtual ScheduleSlot getSlotByIndex(int index) = 0;
};

#endif
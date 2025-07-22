/*
Created by: Zhang Jiahua (2402050)
Date: 19/7/2025
*/

#pragma once

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "IReadScheduler.h"
#include "ScheduleSlot.h"
#include "./Strategies/ScheduleStrategies.h"
#include "../Freight/IReadFreightRecords.h"
#include "../Cargo/IReadCargoRecords.h"

class Scheduler : public IReadScheduler {
private:
    IReadFreightRecords& readFR;
    IReadCargoRecords& readCR;
    ScheduleStrategies* theStrategy;

    vector <ScheduleSlot> slots;

public:
    Scheduler(IReadFreightRecords& readFR, IReadCargoRecords& readCR);

    void setScheduleStrategy(ScheduleStrategies* strategy);
    void generateSchedule();

    int getSlotsSize() override;
    ScheduleSlot getSlotByIndex(int index) override;
    bool isFreightInSchedule(Freight f);
    bool isCargoInSchedule(Cargo c);
};

#endif // !SCHEDULER_H

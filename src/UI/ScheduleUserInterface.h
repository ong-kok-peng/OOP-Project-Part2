/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef SCHEDULE_USERINTERFACE_H
#define SCHEDULE_USERINTERFACE_H

#include "UserInterface.h"
#include "../Data/Freight/FreightDataPool.h"
#include "../Data/Cargo/CargoDataPool.h"
#include "../Business Logic/Scheduler/Scheduler.h"

class ScheduleUserInterface : public UserInterface {
private:
	Scheduler* scheduler;

public:
	ScheduleUserInterface(FreightDataPool& fp, CargoDataPool& cp);
	void waitForKey() override;
	void clearScreen() override;
	void showMenu() override;
	void setScheduleOptionPrompt();
	void runScheduler();
	void displaySchedule();
	void exportFilePrompt();
};

#endif
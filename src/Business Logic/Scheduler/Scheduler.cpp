/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "Scheduler.h"

Scheduler::Scheduler(I_DisplayFreightDataPool& dfp, I_SortFreightDataPool& sfp,
	I_DisplayCargoDataPool& dcp, I_SortCargoDataPool& scp) : displayCP{ dcp }, sortCP{ scp }, displayFP{ dfp }, sortFP{ sfp } {
}

Scheduler::schedulerOutcome Scheduler::setSchedulerOption(string option) {
	schedulerOutcome schO;

	if (option == "BY_CAPACITY") { 
		scheduleStrategy = new ScheduleByCapacity; 
		schO.status = "SUCCESS"; schO.message = "Option is set to " + scheduleStrategy->getName() + ".";
	}
	else if (option == "BY_TIME") { 
		scheduleStrategy = new ScheduleByTime; 
		schO.status = "SUCCESS"; schO.message = "Option is set to " + scheduleStrategy->getName() + ".";
	}
	else { schO.status = "ERROR"; schO.message = "Invalid option selected."; }

	return schO;
}

Scheduler::schedulerOutcome Scheduler::getSchedulerOption() {
	schedulerOutcome schO;

	if (scheduleStrategy == nullptr) { schO.status = "OPTION_NOT_SET"; schO.message = "no option set"; }
	else { schO.status = "OPTION_IS_SET"; schO.message = scheduleStrategy->getName(); }
	
	return schO;
}

Scheduler::schedulerOutcome Scheduler::runScheduler() {
	schedulerOutcome schO; 

	//check for exisitng freight and cargo data pools, by looking if they have at least one data
	if (displayFP.getFreightByIndex(0) == nullptr) { schO.status = "ERROR"; schO.message = "No freight data is found."; return schO; }
	else if (displayCP.getCargoByIndex(0) == nullptr) { schO.status = "ERROR"; schO.message = "No cargo data is found."; return schO; }
	else {
		
	}

	return schO;
}
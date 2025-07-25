/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "ScheduleByTime.h"

ScheduleByTime::ScheduleByTime() {
	name = "ScheduleByTime";
}

string ScheduleByTime::getName() { return name; }

void ScheduleByTime::sortDataPools(I_SortFreightDataPool& sfp, I_SortCargoDataPool& scp) {
	sfp.sortByCapacity();
	scp.sortByQuantity();
}

string ScheduleByTime::matchFreightCargo(string freightDest, string freightTime, string cargoDest, string cargoTime) {
	return "";
}
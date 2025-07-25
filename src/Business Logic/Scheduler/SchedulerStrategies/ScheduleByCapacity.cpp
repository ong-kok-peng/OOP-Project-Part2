/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "ScheduleByCapacity.h"

ScheduleByCapacity::ScheduleByCapacity() {
	name = "ScheduleByCapacity";
}

string ScheduleByCapacity::getName() { return name; }

void ScheduleByCapacity::sortDataPools(I_SortFreightDataPool& sfp, I_SortCargoDataPool& scp) {
	sfp.sortByCapacity();
	scp.sortByQuantity();
}

string ScheduleByCapacity::matchFreightCargo(string freightDest, string freightTime, string cargoDest, string cargoTime) {
	return "";
}	
/*
Created by: Zhang Jiahua (2402050)
Date: 20/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "ScheduleSlot.h"

ScheduleSlot::ScheduleSlot(vector<Freight> freights, vector<Cargo> cargos, int total_fCapacity, int total_cQuantity) :
	freightsInSlot(freights), cargosInSlot(cargos), totalFreightCapacity(total_fCapacity), totalCargoQuantity(total_cQuantity) {}

ScheduleSlot::FreightCargo ScheduleSlot::getFreightCargo() {
	FreightCargo fc;

	fc.freights = freightsInSlot; fc.cargos = cargosInSlot; 
	fc.total_fCapacity = totalFreightCapacity; fc.total_cQuantity = totalCargoQuantity;
	return fc;
}
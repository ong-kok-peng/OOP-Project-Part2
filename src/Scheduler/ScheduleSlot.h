/*
Created by: Zhang Jiahua (2402050)
Date: 20/7/2025
*/

#pragma once

#ifndef SCHEDULE_SLOT_H
#define SCHEDULE_SLOT_H

#include <vector>
#include "../Freight/Freight.h"
#include "../Cargo/Cargo.h"

class ScheduleSlot {
private:
	vector<Freight> freightsInSlot;
	vector <Cargo> cargosInSlot;
	int totalFreightCapacity;
	int totalCargoQuantity;
public:
	struct FreightCargo { vector<Freight> freights = {}; vector<Cargo> cargos = {}; int total_fCapacity = 0; int total_cQuantity = 0; };
	ScheduleSlot(vector<Freight> freights, vector<Cargo> cargos, int total_fCapacity, int total_cQuantity);
	FreightCargo getFreightCargo();
};

#endif
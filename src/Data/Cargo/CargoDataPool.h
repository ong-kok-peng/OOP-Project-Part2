/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#pragma once

#ifndef CARGO_DATAPOOL_H
#define CARGO_DATAPOOL_H

#include <vector>
#include "CargoData.h"

class CargoDataPool  {
private:
	vector<CargoData> freights;

public:
	CargoDataPool();
	void addCargo(CargoData f);
	void editCargo(int index, CargoData f);
	void deleteCargo(int index);
	int getCargoIndexById(string id);
	CargoData* getCargoByIndex(int index);
	void clearAllCargo();
	void sortByTime();
	void sortByCapacity();
};

#endif

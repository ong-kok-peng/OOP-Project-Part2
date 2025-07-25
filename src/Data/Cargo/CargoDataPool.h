/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#pragma once

#ifndef CARGO_DATAPOOL_H
#define CARGO_DATAPOOL_H

#include "I_AddCargoDataPool.h"
#include "I_ModifyCargoDataPool.h"
#include "I_DisplayCargoDataPool.h"
#include "I_SortCargoDataPool.h"

class CargoDataPool : public I_AddCargoDataPool, public I_ModifyCargoDataPool,
	public I_DisplayCargoDataPool, public I_SortCargoDataPool {
private:
	vector<CargoData> cargos;

public:
	CargoDataPool();
	void addCargo(CargoData f);
	void editCargo(int index, CargoData f);
	void deleteCargo(int index);
	vector<int> getCargoIndexsByValue(string value);
	CargoData* getCargoByIndex(int index);
	void clearAllCargo();
	void sortByTime();
	void sortByQuantity();
};

#endif

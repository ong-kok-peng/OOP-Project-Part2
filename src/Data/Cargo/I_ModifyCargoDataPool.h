/*
Created by: Ong Kok Peng (2403435)
Date: 17/7/2025
*/

#pragma once

#include "CargoData.h"

#ifndef I_MODIFYCARGO_DATAPOOL_H
#define I_MODIFYCARGO_DATAPOOL_H

class I_ModifyCargoDataPool {
public:
	virtual void editCargo(int index, CargoData f) = 0;
	virtual void deleteCargo(int index) = 0;
	virtual CargoData* getCargoByIndex(int index) = 0;
};

#endif
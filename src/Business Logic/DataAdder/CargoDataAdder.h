/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#pragma once

#ifndef CARGO_DATAADDER_H
#define CARGO_DATAADDER_H

#include "DataAdder.h"
#include "../../Data/Cargo/I_AddCargoDataPool.h"
#include "../../File Manager/FileReader.h"

class CargoDataAdder : public DataAdder {
private:
	I_AddCargoDataPool& cp;

public:
	CargoDataAdder(I_AddCargoDataPool& cp);
	DataAdder::addOutcome addData(string input) override;
	DataAdder::addOutcome importFromFile(string input) override;
};

#endif

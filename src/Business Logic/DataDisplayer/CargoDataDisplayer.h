/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#pragma once

#ifndef CARGO_DATA_DISPLAYER_H
#define CARGO_DATA_DISPLAYER_H

#include "DataDisplayer.h"
#include "../../Data/Cargo/CargoDataPool.h"

class CargoDataDisplayer : public DataDisplayer {
private:
	CargoDataPool& cp;

public:
	CargoDataDisplayer(CargoDataPool& cp);
	DataDisplayer::searchOutcome searchData(string id) override;
	DataDisplayer::dataValues getDataValues(int index) override;
};

#endif

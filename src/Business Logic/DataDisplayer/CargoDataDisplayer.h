/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#pragma once

#ifndef CARGO_DATA_DISPLAYER_H
#define CARGO_DATA_DISPLAYER_H

#include "DataDisplayer.h"
#include "../../Data/Cargo/I_DisplayCargoDataPool.h"

class CargoDataDisplayer : public DataDisplayer {
private:
	I_DisplayCargoDataPool& cp;

public:
	CargoDataDisplayer(I_DisplayCargoDataPool& cp);
	DataDisplayer::searchOutcome searchData(string id) override;
	DataDisplayer::dataValues getDataValues(int index) override;
};

#endif

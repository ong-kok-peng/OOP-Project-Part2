/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_DATA_DISPLAYER_H
#define FREIGHT_DATA_DISPLAYER_H

#include "DataDisplayer.h"
#include "../../Data/Freight/I_DisplayFreightDataPool.h"

class FreightDataDisplayer : public DataDisplayer {
private:
	I_DisplayFreightDataPool& fp;

public:
	FreightDataDisplayer(I_DisplayFreightDataPool& fp);
	DataDisplayer::searchOutcome searchData(string id) override;
	DataDisplayer::dataValues getDataValues(int index) override;
};

#endif

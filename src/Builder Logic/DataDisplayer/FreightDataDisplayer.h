/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_DATA_DISPLAYER_H
#define FREIGHT_DATA_DISPLAYER_H

#include "DataDisplayer.h"
#include "../../Data/Freight/FreightDataPool.h"

class FreightDataDisplayer : public DataDisplayer {
private:
	FreightDataPool& fp;

public:
	FreightDataDisplayer(FreightDataPool& fp);
	DataDisplayer::searchOutcome searchData(string id) override;
	DataDisplayer::dataValues getDataValues(int index) override;
};

#endif

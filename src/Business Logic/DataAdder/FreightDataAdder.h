/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_DATAADDER_H
#define FREIGHT_DATAADDER_H

#include "DataAdder.h"
#include "../../Data/Freight/FreightDataPool.h"
#include "../../File Manager/FileReader.h"

class FreightDataAdder : public DataAdder {
private:
	FreightDataPool& fp;

public:
	FreightDataAdder(FreightDataPool& fp);
	DataAdder::addOutcome addData(string input) override;
	DataAdder::addOutcome importFromFile(string input) override;
};

#endif

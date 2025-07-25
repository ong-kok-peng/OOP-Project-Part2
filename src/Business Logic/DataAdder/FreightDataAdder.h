/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_DATAADDER_H
#define FREIGHT_DATAADDER_H

#include "DataAdder.h"
#include "../../Data/Freight/I_AddFreightDataPool.h"
#include "../../File Manager/FileReader.h"

class FreightDataAdder : public DataAdder {
private:
	I_AddFreightDataPool& fp;

public:
	FreightDataAdder(I_AddFreightDataPool& fp);
	DataAdder::addOutcome addData(string input) override;
	DataAdder::addOutcome importFromFile(string input) override;
};

#endif

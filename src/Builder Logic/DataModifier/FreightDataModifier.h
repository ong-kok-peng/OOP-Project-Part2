/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_DATA_MODIFIER_H
#define FREIGHT_DATA_MODIFIER_H

#include "DataModifier.h"
#include "../../Data/Freight/FreightDataPool.h"

class FreightDataModifier : public DataModifier {
private:
	FreightDataPool& fp;

public:
	FreightDataModifier(FreightDataPool& fp);
	DataModifier::modifyOutcome editData(int index, std::string input) override;
	DataModifier::modifyOutcome deleteData(int index, char yesNo) override;
};

#endif

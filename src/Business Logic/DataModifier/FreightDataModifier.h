/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_DATA_MODIFIER_H
#define FREIGHT_DATA_MODIFIER_H

#include "DataModifier.h"
#include "../../Data/Freight/I_ModifyFreightDataPool.h"

class FreightDataModifier : public DataModifier {
private:
	I_ModifyFreightDataPool& fp;

public:
	FreightDataModifier(I_ModifyFreightDataPool& fp);
	DataModifier::modifyOutcome editData(int index, std::string input) override;
	DataModifier::modifyOutcome deleteData(int index, char yesNo) override;
};

#endif

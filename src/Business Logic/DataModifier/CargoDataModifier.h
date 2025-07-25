/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#pragma once

#ifndef CARGO_DATA_MODIFIER_H
#define CARGO_DATA_MODIFIER_H

#include "DataModifier.h"
#include "../../Data/Cargo/I_ModifyCargoDataPool.h"

class CargoDataModifier : public DataModifier {
private:
	I_ModifyCargoDataPool& cp;

public:
	CargoDataModifier(I_ModifyCargoDataPool& cp);
	DataModifier::modifyOutcome editData(int index, std::string input) override;
	DataModifier::modifyOutcome deleteData(int index, char yesNo) override;
};

#endif

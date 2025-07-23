/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#include <string>

#ifndef DATA_MODIFIER_H
#define DATA_MODIFIER_H

class DataModifier {
public:
	struct modifyOutcome { std::string status = ""; std::string message = ""; };

	virtual DataModifier::modifyOutcome editData(int index, std::string input) = 0;
	virtual DataModifier::modifyOutcome deleteData(int index, char yesNo) = 0;
};

#endif
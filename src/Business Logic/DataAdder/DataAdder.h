/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#include <string>

#ifndef DATAADDER_H
#define DATAADDER_H

class DataAdder {
public:
	struct addOutcome { std::string status = ""; std::string message = ""; };
	virtual DataAdder::addOutcome addData(std::string input) = 0;
	virtual DataAdder::addOutcome importFromFile(std::string input) = 0;
};

#endif
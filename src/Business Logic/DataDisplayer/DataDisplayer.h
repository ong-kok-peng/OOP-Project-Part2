/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#include <string>
#include <vector>

#ifndef DATA_DISPLAYER_H
#define DATA_DISPLAYER_H

class DataDisplayer {
public:
	struct searchOutcome { std::string status = ""; std::vector<int> indexs = {}; };
	struct dataValues { std::string status = ""; std::string id = "";  std::string destination = ""; std::string time = "";
						std::string extraVal1 = ""; std::string extraVal2 = ""; };

	virtual DataDisplayer::searchOutcome searchData(std::string id) = 0;
	virtual DataDisplayer::dataValues getDataValues(int index) = 0;
};

#endif
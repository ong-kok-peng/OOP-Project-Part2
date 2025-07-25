/*
Created by: Ong Kok Peng (2403435)
Date: 23/7/2025
*/

#pragma once

#include <string>
#include <vector>
#include "../../DataDisplayer/DataDisplayer.h"

#ifndef FILE_FORMAT_STRATEGIES_H
#define FILE_FORMAT_STRATEGIES_H

class FileFormatStrategies {
public:
	virtual std::string createFileExtension() = 0; //common function for all types of data
	virtual std::string createFileHeader(std::vector<std::string> headerValues) = 0;
	virtual std::string createFileLine(DataDisplayer::dataValues& dv) = 0;
};

#endif
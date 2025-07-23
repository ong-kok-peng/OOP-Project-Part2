/*
Created by: Ong Kok Peng (2403435)
Date: 23/7/2025
*/

#pragma once

#include <string>
#include "../../DataDisplayer/DataDisplayer.h"

#ifndef FILE_FORMAT_STRATEGIES_H
#define FILE_FORMAT_STRATEGIES_H

class FileFormatStrategies {
public:
	virtual std::string createFileExtension() = 0; //common function for all types of data

	virtual std::string createFileHeader_Freight() = 0;
	virtual std::string createFileLine_Freight(DataDisplayer::dataValues& dv) = 0;
	//virtual std::string createFileHeader_Cargo() = 0;
	//virtual std::string createFileLine_Cargo(DataDisplayer::dataValues& dv) = 0;
};

#endif
/*
Created by: Ong Kok Peng (2403435)
Date: 23/7/2025
*/

#pragma once

#ifndef CSV_FORMAT_STRATEGIES_H
#define CSV_FORMAT_STRATEGIES_H

#include <vector>
#include "FileFormatStrategies.h"

class CsvFormatStrategy : public FileFormatStrategies {
public:
	string createFileExtension() override;
	string createFileHeader(std::vector<string> headerValues) override;
	string createFileLine(DataDisplayer::dataValues& dv) override;
};

#endif

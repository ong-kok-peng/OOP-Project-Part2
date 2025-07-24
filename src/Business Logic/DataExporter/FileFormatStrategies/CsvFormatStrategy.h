/*
Created by: Ong Kok Peng (2403435)
Date: 23/7/2025
*/

#pragma once

#ifndef CSV_FORMAT_STRATEGIES_H
#define CSV_FORMAT_STRATEGIES_H

#include "FileFormatStrategies.h"

class CsvFormatStrategy : public FileFormatStrategies {
public:
	string createFileExtension() override;

	string createFileHeader_Freight() override;
	string createFileLine_Freight(DataDisplayer::dataValues& dv) override;
	string createFileHeader_Cargo() override;
	string createFileLine_Cargo(DataDisplayer::dataValues& dv) override;
};

#endif

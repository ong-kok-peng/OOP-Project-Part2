/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#include <string>
#include "../../File Manager/FileWriter.h"
#include "./FileFormatStrategies/FileFormatStrategies.h"
#include "./FileFormatStrategies/TxtFormatStrategy.h"
#include "./FileFormatStrategies/CsvFormatStrategy.h"

#ifndef DATA_EXPORTER_H
#define DATA_EXPORTER_H

class DataExporter {
public:
	struct exportOutcome { std::string status = ""; std::string message = ""; };

	virtual DataExporter::exportOutcome setExportFileFormat(string fileFormat) = 0;
	virtual DataExporter::exportOutcome exportToFile(std::string input) = 0;
};

#endif
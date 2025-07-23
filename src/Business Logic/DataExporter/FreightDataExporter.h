/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_DATA_EXPORTER_H
#define FREIGHT_DATA_EXPORTER_H

#include "DataExporter.h"
#include "../DataDisplayer/FreightDataDisplayer.h"

class FreightDataExporter : public DataExporter {
private:
	FreightDataDisplayer& displayFR; //Data Exporter depends on Data Displayer to reuse its getValues function
	FileFormatStrategies* fileFormatStrategy = nullptr;

public:
	FreightDataExporter(FreightDataDisplayer& displayFR);
	DataExporter::exportOutcome setExportFileFormat(string fileFormat) override;
	DataExporter::exportOutcome exportToFile(string input) override;
};

#endif

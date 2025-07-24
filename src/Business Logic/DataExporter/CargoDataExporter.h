/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#pragma once

#ifndef CARGO_DATA_EXPORTER_H
#define CARGO_DATA_EXPORTER_H

#include "DataExporter.h"
#include "../DataDisplayer/CargoDataDisplayer.h"

class CargoDataExporter : public DataExporter {
private:
	CargoDataDisplayer& displayCR; //Data Exporter depends on Data Displayer to reuse its getValues function
	FileFormatStrategies* fileFormatStrategy = nullptr;

public:
	CargoDataExporter(CargoDataDisplayer& displayCR);
	DataExporter::exportOutcome setExportFileFormat(string fileFormat) override;
	DataExporter::exportOutcome exportToFile(string input) override;
};

#endif

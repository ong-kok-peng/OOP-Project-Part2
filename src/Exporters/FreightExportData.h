/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 18/7/2025
*/

#pragma once

#ifndef FREIGHT_EXPORT_DATA_H
#define FREIGHT_EXPORT_DATA_H

#include "IExportData.h"
#include "../Freight/IReadFreightRecords.h"

class FreightExportData : public IExportData {
private:
	IReadFreightRecords& readFR;

public:
	FreightExportData(IReadFreightRecords& readFR);
	void exportRecords() override;
};

#endif

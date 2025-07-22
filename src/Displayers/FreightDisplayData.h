/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_DISPLAY_DATA_H
#define FREIGHT_DISPLAY_DATA_H

#include "IDisplayData.h"
#include "../Freight/IReadFreightRecords.h"

class FreightDisplayData : public IDisplayData {
private:
	IReadFreightRecords& readFR;

public:
	FreightDisplayData(IReadFreightRecords& readFR);
	void displayData() override;
	//void sortRecords(); //uncomment this if testing sort
};

#endif

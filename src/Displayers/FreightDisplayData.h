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
	void displayRecords() override;
};

#endif

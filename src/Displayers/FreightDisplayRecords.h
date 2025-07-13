#pragma once

#ifndef FREIGHT_DISPLAY_RECORDS_H
#define FREIGHT_DISPLAY_RECORDS_H

#include "IDisplayRecords.h"
#include "../Freight/IReadFreightRecords.h"

class FreightDisplayRecords : public IDisplayRecords {
private:
	IReadFreightRecords& readFR;

public:
	FreightDisplayRecords(IReadFreightRecords& readFR);
	void displayRecords() override;
};

#endif

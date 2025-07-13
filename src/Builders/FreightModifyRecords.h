#pragma once

#ifndef FREIGHT_MODIFY_RECORDS_H
#define FREIGHT_MODIFY_RECORDS_H

#include "IModifyRecords.h"
#include "../Freight/FreightRecords.h"

class FreightModifyRecords : public IModifyRecords {
private:
	FreightRecords& fr;

public:
	FreightModifyRecords(FreightRecords& fr);
	void editRecord() override;
	void deleteRecord() override;
};

#endif

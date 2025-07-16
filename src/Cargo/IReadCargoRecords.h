#pragma once

#ifndef I_READ_CARGO_RECORDS_H
#define I_READ_CARGO_RECORDS_H

#include "Cargo.h"

class IReadCargoRecords{
public:
	virtual int getRecordsSize() = 0;
	virtual Cargo getCargo(int index) = 0;
	virtual void sortCargoByTime() = 0;
	virtual void sortCargoByQuantity() = 0;
	virtual std::vector<Cargo> getAllRecords() const = 0;
    virtual ~IReadCargoRecords() = default;
};

#endif
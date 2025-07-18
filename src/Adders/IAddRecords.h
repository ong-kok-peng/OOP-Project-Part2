/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef I_ADD_RECORDS_H
#define I_ADD_RECORDS_H

class IAddRecords {
public:
	virtual void addRecord() = 0;
	virtual void addRecordsFromFile() = 0;
};

#endif
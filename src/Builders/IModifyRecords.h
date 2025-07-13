#pragma once

#ifndef I_MODIFY_RECORDS_H
#define I_MODIFY_RECORDS_H

class IModifyRecords {
public:
	virtual void editRecord() = 0;
	virtual void deleteRecord() = 0;
};

#endif
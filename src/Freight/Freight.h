#pragma once

#ifndef FREIGHT_H
#define FREIGHT_H

#include "../TransportEntity/TransportEntity.h"

class Freight : public TransportEntity {
private:
	string id;
	string name;
	int capacity;
public:
	Freight();
	bool setId(string id);
	bool setName(string name);
	string getId();
	string getName();
	int getCapacity();
};

#endif


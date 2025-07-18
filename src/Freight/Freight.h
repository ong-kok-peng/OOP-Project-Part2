/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

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
	int getCapacity();
	string getId() const;
	string getName() const;

};

#endif


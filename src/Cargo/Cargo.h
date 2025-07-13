#pragma once

#ifndef CARGO_H
#define CARGO_H

#include "../TransportEntity/TransportEntity.h"

class Cargo : public TransportEntity {
private:
	string id;
	string name;
	int quantity;
public:
	Cargo();
	bool setId(string id);
	bool setQuantity(int quantity);
	string getId();
	int getQuantity();
};

#endif

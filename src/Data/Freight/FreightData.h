/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHTDATA_H
#define FREIGHTDATA_H

#include "../TransportEntity.h"

class FreightData : public TransportEntity {
private:
    string id;
    string name;
    int capacity;

public:
    FreightData();  // Default constructor

    // Setters
    validationOutcome setValues(string id, string dest, string time, string name);

    // Getters
    string getId();
    string getName();
    int getCapacity();
};

#endif

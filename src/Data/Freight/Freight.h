/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_H
#define FREIGHT_H

#include "../TransportEntity.h"

class Freight : public TransportEntity {
private:
    string id;
    string name;
    int capacity;

public:
    Freight();  // Default constructor

    // Setters
    validationOutcome setValues(string id, string dest, string time, string name);

    // Getters
    string getId();
    string getName();
    int getCapacity();
};

#endif

/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef CARGO_H
#define CARGO_H

#include "../TransportEntity.h"

class Cargo : public TransportEntity {
private:
    string id;
    int quantity;

public:
    Cargo();  // Default constructor

    // Setters
    validationOutcome setValues(string id, string dest, string time, string quantity);

    // Getters
    string getId();
    int getQuantity();
};

#endif

/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#pragma once

#ifndef CARGODATA_H
#define CARGODATA_H

#include "../TransportEntity.h"

class CargoData : public TransportEntity {
private:
    string id;
    int quantity;

public:
    CargoData();  // Default constructor

    // Setters
    validationOutcome setValues(string id, string dest, string time, string quantity);

    // Getters
    string getId();
    int getQuantity();
};

#endif

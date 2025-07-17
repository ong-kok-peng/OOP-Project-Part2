#pragma once

#ifndef CARGO_H
#define CARGO_H

#include "../TransportEntity/TransportEntity.h"
#include <string>

class Cargo : public TransportEntity {
private:
    std::string id;
    std::string destination;
    std::string time;
    int quantity;

public:
    Cargo();  // Default constructor

    // Setters
    bool setId(std::string id);
    bool setQuantity(int quantity);

    // Getters
    std::string getId() const;
    int getQuantity() const;
};

#endif

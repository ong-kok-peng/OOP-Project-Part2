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
    Cargo(std::string id, std::string dest, std::string time, int quantity);  // Custom constructor

    // Setters
    bool setId(std::string id);
    bool setQuantity(int quantity);
    void setDestination(std::string dest);
    void setTime(std::string time);

    // Getters
    std::string getId() const;
    std::string getDestination() const;
    std::string getTime() const;
    int getQuantity() const;
};

#endif

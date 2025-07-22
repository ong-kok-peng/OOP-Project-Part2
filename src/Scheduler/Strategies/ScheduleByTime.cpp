/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "ScheduleByTime.h"

ScheduleByTime::ScheduleByTime() {
    ScheduleStrategies::name = "ScheduleByTime";
    freightIndex = 0; cargoIndex = 0; cumulatedCapacity = 0; cumulatedQuantity = 0;
    matchedFreightsBlk = {}; matchedCargosBlk = {};
}

ScheduleByTime::scheduleMatchUpdate ScheduleByTime::matchFreightCargo(Freight f, Cargo c) {
    scheduleMatchUpdate update;

    bool isDestinationMatched = (f.getDestination() == c.getDestination());
    string timeMatched = compareTimeFromRecords(f.getTime(), c.getTime());

    if (isDestinationMatched && timeMatched == "MATCHED") {
        //both freight and cargo match in dest and time, cumulate the capacity and quantity
        if (cumulatedCapacity != f.getCapacity()) { cumulatedCapacity += f.getCapacity(); }
        if (cumulatedQuantity != c.getQuantity()) { cumulatedQuantity += c.getQuantity(); }

        //cumulate the matched freight and cargo as long as its unique
        if (matchedFreightsBlk.empty()) { matchedFreightsBlk.push_back(f); }
        else if (matchedFreightsBlk.back().getId() != f.getId()) { matchedFreightsBlk.push_back(f); }
        if (matchedCargosBlk.empty()) { matchedCargosBlk.push_back(c); }
        else if (matchedCargosBlk.back().getId() != c.getId()) { matchedCargosBlk.push_back(c); }

        if (cumulatedCapacity > cumulatedQuantity) { cargoIndex++; }         //current freight occupies all the cargo, find the next matching cargo until no match
        else if (cumulatedCapacity < cumulatedQuantity) { freightIndex++; }  //current freight is not enough for all the cargo, find the next matching freight until no match
        else { freightIndex++; cargoIndex++; }                               //both current freight and cargo exact size, move on
    }
    else {
        if (matchedFreightsBlk.size() > 0 && matchedCargosBlk.size() > 0) {
            //after prior matche(s), no more consecutive match, check for excess cargo

            if (cumulatedCapacity < cumulatedQuantity) {
                //overflow, excess cargo
                int excessQuantity = cumulatedQuantity - cumulatedCapacity; cumulatedQuantity = cumulatedCapacity;
                matchedCargosBlk.back().setQuantity(matchedCargosBlk.back().getQuantity() - excessQuantity); //remove excess quantity from the last cargo
            }
            //finally, add schedule slot
            update.freightIndex = freightIndex; update.cargoIndex = cargoIndex; update.isSlotCreated = true; 
            update.newSlot = new ScheduleSlot(matchedFreightsBlk, matchedCargosBlk, cumulatedCapacity, cumulatedQuantity);

            //reset matches for next possible match
            cumulatedCapacity = 0; cumulatedQuantity = 0;
            matchedFreightsBlk.clear(); matchedCargosBlk.clear();

            return update;
        }
        else {
            //no prior matches at all
            if ((f.getDestination() < c.getDestination()) ||
                (f.getDestination() == c.getDestination() && timeMatched == "EARLY_CARGO")) { freightIndex++; } //freight is unmatched

            else { cargoIndex++; } //cargo is unmatched
        }
    }
    //return updated indexes
    update.freightIndex = freightIndex; update.cargoIndex = cargoIndex; return update;
}
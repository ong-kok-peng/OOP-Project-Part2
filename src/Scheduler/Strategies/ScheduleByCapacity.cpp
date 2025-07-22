/*
Created by: Zhang Jiahua (2402050)
Date: 22/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "ScheduleByCapacity.h"

ScheduleByCapacity::ScheduleByCapacity() {
    ScheduleStrategies::name = "ScheduleByCapacity";
    freightIndex = 0; cargoIndex = 0; cumulatedCapacity = 0; cumulatedQuantity = 0;
    matchedFreightsBlk = {}; matchedCargosBlk = {};
}

ScheduleByCapacity::scheduleMatchUpdate ScheduleByCapacity::matchFreightCargo(Freight f, Cargo c) {
    scheduleMatchUpdate update;

    if (!loopCargos) {
        if (f.getDestination() < c.getDestination()) {
            //return to while loop with updated indexes
            freightIndex++; 
            update.freightIndex = freightIndex; update.cargoIndex = cargoIndex; return update;
        }
        if (f.getDestination() > c.getDestination()) {
            //return to while loop with updated indexes
            cargoIndex++; 
            update.freightIndex = freightIndex; update.cargoIndex = cargoIndex; return update;
        }

        //new destination matches
        matchedDest = f.getDestination();
        cargoIndxStart = cargoIndex;
        loopCargos = true;
    }
    //within same freight, loop cargos, check if time matches
    string timeMatched = compareTimeFromRecords(f.getTime(), c.getTime());

    if (timeMatched == "MATCHED") {
        cumulatedQuantity += c.getQuantity();

        if (f.getCapacity() > cumulatedQuantity) {
            matchedCargosBlk.push_back(c); //add in cargo(s) that can fully fill in
        }
        else if (f.getCapacity() <= cumulatedQuantity) {
            //freight capacity has reached, and stop finding more cargo
            //if freight overflows, remove excess quantity of last cargo
            cumulatedCargoFull = true;
            int excessQuantity = cumulatedQuantity - f.getCapacity(); cumulatedQuantity = f.getCapacity(); //set cumulated quantity to max value
            c.setQuantity(c.getQuantity() - excessQuantity); matchedCargosBlk.push_back(c);
        }
    }

    if (cargoIndex + 1 < readCR.getRecordsSize()) {
        cargoIndex++; Cargo nextCargo = readCR.getCargoByIndex(cargoIndex);

        if (nextCargo.getDestination() != matchedDest || cumulatedCargoFull) {
            //all cargo that match freight's destination is looped, add schedule slot if there's cumulated cargo
            if (matchedCargosBlk.size() > 0) {
                matchedFreightsBlk.push_back(f);
            }
            cumulatedCargoFull = false;

            if (freightIndex + 1 < readFR.getRecordsSize()) {
                freightIndex++; Freight nextFreight = readFR.getFreightByIndex(freightIndex);

                if (nextFreight.getDestination() == matchedDest) { cargoIndex = cargoIndxStart; }
                else { loopCargos = false; }

                //reset matches for next possible match
                cumulatedCapacity = 0; cumulatedQuantity = 0;
                matchedFreightsBlk.clear(); matchedCargosBlk.clear();

                //return with a new schedule slot (if there's any) and updated indexes
                update.freightIndex = freightIndex; update.cargoIndex = cargoIndex; update.isSlotCreated = true;
                update.newSlot = new ScheduleSlot(matchedFreightsBlk, matchedCargosBlk, cumulatedCapacity, cumulatedQuantity);
                return update;
            }
            else { 
                // reached to the end of freights. return to stop the while loop
                update.freightIndex = freightIndex; update.cargoIndex = cargoIndex;
                update.schedulerStatus = "STOPPED";
                return update;
            } 
        }
    }
    else {
        //reached to the end of cargos. create a schedule slot if there are matched cargo(s)
        //then return to stop the while loop
        if (matchedCargosBlk.size() > 0) {
            matchedFreightsBlk.push_back(f);
        }
        cumulatedCargoFull = false;
        update.schedulerStatus = "STOPPED";
        update.freightIndex = freightIndex; update.cargoIndex = cargoIndex; update.isSlotCreated = true;
        update.newSlot = new ScheduleSlot(matchedFreightsBlk, matchedCargosBlk, cumulatedCapacity, cumulatedQuantity);
        return update;
    }
    //return updated indexes
    update.freightIndex = freightIndex; update.cargoIndex = cargoIndex; return update;
}
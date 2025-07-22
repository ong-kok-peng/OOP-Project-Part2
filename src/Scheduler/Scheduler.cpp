/*
Created by: Zhang Jiahua (2402050)
Date: 19/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "Scheduler.h"

Scheduler::Scheduler(IReadFreightRecords& readFR, IReadCargoRecords& readCR) : readFR{ readFR }, readCR{ readCR } {
    slots = {}; theStrategy = nullptr;
}

void Scheduler::setScheduleStrategy(ScheduleStrategies* strategy) {
    theStrategy = strategy;
}

void Scheduler::generateSchedule() {
	if (readFR.getRecordsSize() == 0 || readCR.getRecordsSize() == 0) {
		cout << "There are no freight/cargo records. Add a new record or import from a file.\n";
		return;
	}

    cout << "Generating schedule using strategy " << theStrategy->name << "\n";

    if (theStrategy->name == "ScheduleByTime") {
        readFR.sortFreightByTime(); readCR.sortCargoByTime();
    }
    else if (theStrategy->name == "ScheduleByCapacity") {
        readFR.sortFreightByCapacity(); readCR.sortCargoByQuantity();
    }

    int freightIndx = 0, cargoIndx = 0;

	while (freightIndx < readFR.getRecordsSize() && cargoIndx < readCR.getRecordsSize()) {
		Freight f = readFR.getFreightByIndex(freightIndx); Cargo c = readCR.getCargoByIndex(cargoIndx);

        ScheduleStrategies::scheduleMatchUpdate schedulerUpdate = theStrategy->matchFreightCargo(f, c);
        
        if (schedulerUpdate.schedulerStatus == "STOPPED") { break; }
        else {
            if (schedulerUpdate.isSlotCreated) {
                slots.push_back(*schedulerUpdate.newSlot);
            }
            freightIndx = schedulerUpdate.freightIndex; cargoIndx = schedulerUpdate.cargoIndex;
        }
        
	}

    cout << "\nSchedule is generated! Press enter to go back.\n";
}

int Scheduler::getSlotsSize() { return slots.size(); }

ScheduleSlot Scheduler::getSlotByIndex(int index) { return slots[index]; }

bool Scheduler::isFreightInSchedule(Freight f) {
    for (auto slot : slots) {
        vector<Freight> freightsInSlot = slot.getFreightCargo().freights;
        auto iterator = find_if(freightsInSlot.begin(), freightsInSlot.end(), [f](Freight& freightInSlot) {
            return f.getId() == freightInSlot.getId();
            });

        if (iterator != freightsInSlot.end()) { return true; break; }
    }
    return false;
}

bool Scheduler::isCargoInSchedule(Cargo c) {
    for (auto& slot : slots) {
        vector<Cargo> cargosInSlot = slot.getFreightCargo().cargos;
        auto iterator = find_if(cargosInSlot.begin(), cargosInSlot.end(), [c](Cargo& cargoInSlot) {
            return c.getId() == cargoInSlot.getId();
            });

        if (iterator != cargosInSlot.end()) { return true; break; }
    }
    return false;
}

#include "../Freight/FreightRecords.h"
#include "../Cargo/CargoRecords.h"
#include "../Adders/FreightAddRecords.h"
#include "../Adders/CargoAddRecords.h"
#include "./Strategies/ScheduleByTime.h"
#include "./Strategies/ScheduleByCapacity.h"

int main() {
    FreightRecords fr; CargoRecords cr;
    FreightAddRecords addFR(fr); CargoAddRecords addCR(cr);
    Scheduler scheduler(fr, cr);
    ScheduleByTime timeScheduler; //ScheduleByCapacity capacityScheduler;

    addFR.addRecordsFromFile();
    addCR.addRecordsFromFile();
    scheduler.setScheduleStrategy(&timeScheduler);
    scheduler.generateSchedule();

    cout << "\n";
    for (int a = 0; a < scheduler.getSlotsSize(); a++) {
        ScheduleSlot::FreightCargo slotFC = scheduler.getSlotByIndex(a).getFreightCargo();
        cout << "Schedule slot " << (a + 1) << ":\n";
        cout << "Total freight capacity: " << slotFC.total_fCapacity << "; Total cargo quantity: " << slotFC.total_cQuantity << ".\n";
        cout << "Capacity fully filled: " << (slotFC.total_fCapacity == slotFC.total_cQuantity) << "\n\n";
        cout << "Freight(s):\n";
        for (auto& f : slotFC.freights) {
            cout << "Freight ID: " << f.getId() << ", Name: " << f.getName() << ", Destination: " << f.getDestination() << ", Refuel time: " << f.getTime() << "\n";
        }
        cout << "Cargo(s):\n";
        for (auto& c : slotFC.cargos) {
            cout << "ID: " << c.getId() << ", Destination: " << c.getDestination() << ", Arrival time: " << c.getTime() << ", Quantity: " << c.getQuantity() << "\n";
        }
        cout << "\n";
    }
    cout << "\nUnmatched Freight(s):\n";
    for (int fIndex = 0; fIndex < fr.getRecordsSize(); fIndex++) {
        Freight f = fr.getFreightByIndex(fIndex);
        if (!scheduler.isFreightInSchedule(f)) {
            cout << "Freight ID: " << f.getId() << ", Name: " << f.getName() << ", Destination: " << f.getDestination() << ", Refuel time: " << f.getTime() << "\n";
        }
    }
    cout << "\nUnmatched Cargo(s):\n";
    for (int cIndex = 0; cIndex < cr.getRecordsSize(); cIndex++) {
        Cargo c = cr.getCargoByIndex(cIndex);
        if (!scheduler.isCargoInSchedule(c)) {
            cout << "ID: " << c.getId() << ", Destination: " << c.getDestination() << ", Arrival time: " << c.getTime() << ", Quantity: " << c.getQuantity() << "\n";
        }
    }
    return 0;
}

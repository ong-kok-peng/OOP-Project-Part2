#include "CargoModifyRecords.h"
#include "../Cargo/Cargo.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor
CargoModifyRecords::CargoModifyRecords(CargoRecords& cr) : cargoRecords(cr) {}

// Modify a cargo record at a given index
void CargoModifyRecords::modifyRecord(int index) {
    string id, destination, time, quantity;

    cout << "Enter new Cargo ID: ";
    getline(cin, id);
    cout << "Enter new Destination: ";
    getline(cin, destination);
    cout << "Enter new Time: ";
    getline(cin, time);
    cout << "Enter new Quantity: ";
    getline(cin, quantity);

    Cargo updatedCargo(id, destination, time, stoi(quantity));
    cargoRecords.editCargoRecord(index, updatedCargo);

    cout << "Cargo record updated successfully." << endl;
}

// Delete a cargo record at a given index
void CargoModifyRecords::deleteRecord(int index) {
    cargoRecords.deleteCargoRecord(index);
    cout << "Cargo record deleted successfully." << endl;
}

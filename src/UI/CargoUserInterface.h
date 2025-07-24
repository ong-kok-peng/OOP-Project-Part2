/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#pragma once

#ifndef CARGO_USERINTERFACE_H
#define CARGO_USERINTERFACE_H

#include "UserInterface.h"
#include "../Data/Cargo/CargoDataPool.h"
#include "../Business Logic/DataAdder/CargoDataAdder.h"
#include "../Business Logic/DataModifier/CargoDataModifier.h"
#include "../Business Logic/DataDisplayer/CargoDataDisplayer.h"
#include "../Business Logic/DataExporter/CargoDataExporter.h"

class CargoUserInterface : public UserInterface {
private:
	CargoDataPool cp;
	CargoDataAdder* addCP;
	CargoDataModifier* modifyCP;
	CargoDataDisplayer* displayCP;
	CargoDataExporter* exportCP;

public:
	CargoUserInterface();
	void waitForKey() override;
	void clearScreen() override;
	void showMenu() override;
	void addCargoPrompt();
	void importFilePrompt();
	void exportFilePrompt();
	void deleteCargoPrompt();
	void editCargoPrompt();
	void displayCargo();
};

#endif
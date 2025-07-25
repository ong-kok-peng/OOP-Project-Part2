/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#pragma once

#ifndef FREIGHT_USERINTERFACE_H
#define FREIGHT_USERINTERFACE_H

#include "UserInterface.h"
#include "../Data/Freight/FreightDataPool.h"
#include "../Business Logic/DataAdder/FreightDataAdder.h"
#include "../Business Logic/DataModifier/FreightDataModifier.h"
#include "../Business Logic/DataDisplayer/FreightDataDisplayer.h"
#include "../Business Logic/DataExporter/FreightDataExporter.h"

class FreightUserInterface : public UserInterface {
private:
	FreightDataAdder* addFP;
	FreightDataModifier* modifyFP;
	FreightDataDisplayer* displayFP;
	FreightDataExporter* exportFP;

public:
	FreightUserInterface(FreightDataPool& fp);
	void waitForKey() override;
	void clearScreen() override;
	void showMenu() override;
	void addFreightPrompt();
	void importFilePrompt();
	void exportFilePrompt();
	void deleteFreightPrompt();
	void editFreightPrompt();
	void displayFreight();
};

#endif
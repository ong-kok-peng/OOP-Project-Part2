/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/


#include <iostream>
#include <string>

using namespace std;

#include "src/Freight/FreightRecords.h"
#include "src/Cargo/CargoRecords.h"

#include "src/Builders/FreightAddRecords.h"
#include "src/Builders/FreightModifyRecords.h"
#include "src/Displayers/FreightDisplayData.h"

#include "src/Builders/CargoAddRecords.h"
#include "src/Builders/CargoModifyRecords.h"
#include "src/Displayers/CargoDisplayData.h"

//local function prototype
void showDataMenu(int mainMenuSelection, FreightRecords& fr, CargoRecords& cr);
void clearScreen();
void waitForKey();

void waitForKey() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Press enter to continue...\n";
    cin.get();
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
}

void showDataMenu(int mainMenuSelection, FreightRecords &fr, CargoRecords &cr) {
    string mode;

    //initialize builder, displayer and exporter objects
    FreightAddRecords addFR(fr); FreightModifyRecords modifyFR(fr); FreightDisplayData displayFR(fr);
    CargoAddRecords addCR(cr); CargoModifyRecords modifyCR(cr); CargoDisplayData displayCR(cr);

    if (mainMenuSelection == 1) { mode = "Freight"; }
    else if (mainMenuSelection == 2) { mode = "Cargo"; }

    while (true) {
        int option;

        clearScreen();
        cout << "\n------- Menu for " << mode << ": Please select an option ---------\n";
        cout << "1. Open/re-open " << mode << " records file\n";
        cout << "2. Display " << mode << " records.\n";
        cout << "3. Add " << mode << " record.\n";
        cout << "4. Delete " << mode << " record.\n";
        cout << "5. Edit " << mode << " record.\n";
        cout << "6. Save " << mode << " records to a new file\n";
        cout << "0. Go back.\n";
        cout << "Option: ";

        cin >> option;

        if (cin.fail()) {
            cout << "\nInvalid input. Please enter any number from 0 to 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            waitForKey();
            continue;
        }

        switch (option) {
        case 0:
            return;
            break;
        case 1: {
            //load freighter/cargoItem data from text file
            clearScreen();
            if (mainMenuSelection == 1) { addFR.addRecordsFromFile(); }
            else if (mainMenuSelection == 2) { addCR.addRecordsFromFile(); } 
            waitForKey();
            break;
        }
        case 2:
            //display freighter/cargoItem data 
            clearScreen();
            if (mainMenuSelection == 1) { displayFR.displayRecords(); }
            else if (mainMenuSelection == 2) { displayCR.displayRecords(); } 
            waitForKey();
            break;
        case 3:
            //add freighter/cargoItem data 
            clearScreen();
            if (mainMenuSelection == 1) { addFR.addRecord(); }
            else if (mainMenuSelection == 2) { addCR.addRecord(); } 
            waitForKey();
            break;
        case 4:
            //delete freighter/cargoItem data 
            clearScreen();
            if (mainMenuSelection == 1) { modifyFR.deleteRecord(); }
            else if (mainMenuSelection == 2) { modifyCR.deleteRecord(); } 
            waitForKey();
            break;
        case 5:
            //edit freighter/cargoItem data 
            clearScreen();
            if (mainMenuSelection == 1) { modifyFR.editRecord(); }
            else if (mainMenuSelection == 2) { modifyCR.editRecord(); }
            waitForKey();
            break;
        case 6:
            //save freighter/cargoItem data to a new file
            clearScreen();
            if (mainMenuSelection == 1) { } //exportFreightRecord();
            else if (mainMenuSelection == 2) { } //exportCargoRecord();
            waitForKey();
            break;
        default:
            cout << "\nInvalid option, please type any number from 1 to 6.\n";
            waitForKey();
        }
    }
}

int main() {
    //initialize business data objects
    FreightRecords fr; CargoRecords cr;

    while (true) {
        int mainMenuSelection;

        clearScreen();
        cout << "\n-----------------------------------------------------";
        cout << "\n------- Freight & Cargo Scheduler -------------------\n";
        cout << "1. Work with Freight data.\n";
        cout << "2. Work with Cargo data.\n";
        cout << "3. Generate flight schedule.\n";
        cout << "4. Display generated flight schedule.\n";
        cout << "5. Save generated flight schedule to file.\n";
        cout << "6. Exit program.\n";
        cout << "Option: ";
        cin >> mainMenuSelection;

        if (cin.fail()) {
            cout << "\nInvalid input. Please enter any number from 1 to 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            waitForKey();
            continue;
        }

        switch (mainMenuSelection) {
        case 1:
            clearScreen();
            showDataMenu(mainMenuSelection, fr, cr);
            break;
        case 2:
            clearScreen();
            showDataMenu(mainMenuSelection, fr, cr);
            break;
        case 3:
            clearScreen();
            //generateSchedule();
            waitForKey();
            break;
        case 4:
            clearScreen();
            //dispSchedule();
            waitForKey();
            break;
        case 5:
            clearScreen();
            //saveScheduleToFile();
            waitForKey();
            break;
        case 6:
            cout << "\nProgram exited. Goodbye!\n";
            exit(0);
        default:
            cout << "\nInvalid option, please type any number from 1 to 6.\n";
            waitForKey();
        }
    }
    return 0;
}

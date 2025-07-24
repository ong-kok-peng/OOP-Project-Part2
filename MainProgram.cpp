/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>

using namespace std;

#include "src/UI/FreightUserInterface.h"
#include "src/UI/CargoUserInterface.h"

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

int main() {
	CargoUserInterface cargoUI;
	FreightUserInterface freightUI;

    while (true) {
        int mainMenuSelection;

        clearScreen();
        cout << "-----------------------------------------------------";
        cout << "\n------- Freight & Cargo Scheduler -------------------\n";
        cout << "1. Work with Freight data.\n";
        cout << "2. Work with Cargo data.\n";
        cout << "3. Work with Scheduler.\n";
        cout << "0. Exit program.\n";
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
        case 0:
            cout << "\nProgram exited. Goodbye!\n";
            exit(0);
        case 1:
            clearScreen(); freightUI.showMenu();
            break;
        case 2:
            clearScreen(); cargoUI.showMenu();
            break;
        case 3:
            clearScreen(); //scheduleUI.showMenu();
            break;
        default:
            cout << "\nInvalid option, please type any number from 1 to 6.\n";
            waitForKey();
        }
    }
    return 0;
}
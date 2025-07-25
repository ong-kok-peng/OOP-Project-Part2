/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "ScheduleUserInterface.h"

ScheduleUserInterface::ScheduleUserInterface() {
}

void ScheduleUserInterface::waitForKey() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Press enter to continue...\n";
    cin.get();
}

void ScheduleUserInterface::clearScreen() {
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
}

void ScheduleUserInterface::showMenu() {
    while (true) {
        int option;

        clearScreen();
        cout << "------- Menu for Scheduler: Please select an option ---------\n";
        cout << "1. Select scheduling option.\n";
        cout << "2. Run scheduler.\n";
        cout << "3. Display schedule\n";
        cout << "4. Export schedule to a new file.\n";
        cout << "0. Go back.\n";
        cout << "Option: ";

        cin >> option;

        if (cin.fail()) {
            cout << "\nInvalid input. Please enter any number from 0 to 4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            waitForKey();
            continue;
        }

        switch (option) {
        case 0:
            return;
            break;
        case 1:
            clearScreen(); setScheduleOptionPrompt(); waitForKey(); //set Schedule option
            break;
        case 2:
            clearScreen(); runScheduler(); waitForKey(); //generate the schedule
            break;
        case 3:
            clearScreen(); displaySchedule(); waitForKey(); //display schedule
            break;
        case 4:
            clearScreen(); exportFilePrompt(); waitForKey(); //export schedule to file
            break;
        default:
            cout << "\nInvalid option, please type any number from 0 to 4.\n";
            waitForKey();
        }
    }
}

void ScheduleUserInterface::setScheduleOptionPrompt() {

}

void ScheduleUserInterface::runScheduler() {

}

void ScheduleUserInterface::displaySchedule() {

}

void ScheduleUserInterface::exportFilePrompt() {

}

/* test main code
int main() {
    ScheduleUserInterface sInterface;
    sInterface.showMenu();

    return 0;
}
*/
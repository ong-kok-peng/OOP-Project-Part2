/*
Created by: Yeo Zi Xuan Augustine (2403343)
Date: 17/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "CargoUserInterface.h"

CargoUserInterface::CargoUserInterface(CargoDataPool& cp) {
    addCP = new CargoDataAdder(cp);
    modifyCP = new CargoDataModifier(cp);
    displayCP = new CargoDataDisplayer(cp);
    exportCP = new CargoDataExporter(*displayCP);
}

void CargoUserInterface::waitForKey() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Press enter to continue...\n";
    cin.get();
}

void CargoUserInterface::clearScreen() {
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
}

void CargoUserInterface::showMenu() {
    while (true) {
        int option;

        clearScreen();
        cout << "------- Menu for Cargo: Please select an option ---------\n";
        cout << "1. Open/re-open Cargo records file\n";
        cout << "2. Display Cargo records.\n";
        cout << "3. Add Cargo record.\n";
        cout << "4. Delete Cargo record.\n";
        cout << "5. Edit Cargo record.\n";
        cout << "6. Save Cargo records to a new file\n";
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
        case 1: 
            clearScreen(); importFilePrompt(); waitForKey(); //load cargo data from text file
            break;
        case 2:
            clearScreen(); displayCargo(); waitForKey();  //display cargo data 
            break;
        case 3:
            clearScreen(); addCargoPrompt(); waitForKey();  //add cargo data 
            break;
        case 4:
            clearScreen(); deleteCargoPrompt(); waitForKey(); //delete cargo data
            break;
        case 5:
            clearScreen(); editCargoPrompt(); waitForKey(); //edit cargo data
            break;
        case 6:
            clearScreen(); exportFilePrompt(); waitForKey(); //export cargo data
            break;
        default:
            cout << "\nInvalid option, please type any number from 1 to 6.\n";
            waitForKey();
        }
    }
}

void CargoUserInterface::addCargoPrompt() {
    cout << "------ Adding New Cargo Record ------\n\n";
    cout << "Enter the ID you wish to add.\n";
    cout << "To go back, type \"CANCEL\".\n\n-> ";
    string id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
    getline(cin, id);

    //try to find Cargo with the ID first
    DataDisplayer::searchOutcome searchO = displayCP->searchData(id);
    if (searchO.status == "CANCELLED") { cout << "\nAdd Cargo is cancelled. Press enter to go back.\n"; }

    else if (searchO.status == "DATA_NOT_FOUND") {
        //ID doesn't exist, prompt user to add a new cargo record

        cout << "\nEnter the destination, time and quantity, separated with a comma in between.\n";
        cout << "To go back, type \"CANCEL\".\n\n-> ";
        string userInput;
        getline(cin, userInput);

        if (userInput == "CANCEL") { cout << "\nAdd Cargo is cancelled. Press enter to go back.\n"; return; }
        if (userInput.empty()) { cout << "\nBlank user input. Press enter to go back.\n"; return; }

        CargoDataAdder::addOutcome addO = addCP->addData(id + ", " + userInput);
        cout << "\n" << addO.message << " Press enter to go back.\n";
    }
    else if (searchO.status == "DATA_FOUND" && searchO.indexs.size() == 1) {
        //ID already exists, if quantity is 1 to 9, prompt user to append if desired
        //also, show user the current record details
        DataDisplayer::dataValues dv = displayCP->getDataValues(searchO.indexs[0]);
        int oldQuantity = stoi(dv.extraVal1); //dont need try catch because the quantity is confirmed a number due to validation

        if (oldQuantity < 10) {
            cout << "\nID already exists; the record values are:\n";
            cout << "Destination: " << dv.destination << "; Time: " << dv.time << "; Quantity: " << dv.extraVal1 << ".\n\n";
            cout << "Would you like to add more quantity? Enter additional quantity or 0 to cancel.\n";
            cout << "Note that if you enter a negative number, it will become positive automatically.\n-> ";

            int removeQuantity; cin >> removeQuantity;
            if(cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }
            if (removeQuantity == 0) { cout << "\nAppend cargo cancelled. Press enter to go back.\n"; return; }

            int updatedQuantity = oldQuantity + abs(removeQuantity);
            if (updatedQuantity > 10) { cout << "Error: updated quantity exceeds max 10 quantity. Press enter to go back.\n"; }
            else {
                //if additional quantity is acceptable, edit that particular data with only quantity changed.
                string editInput = ", , " + to_string(updatedQuantity);
                DataModifier::modifyOutcome editO = modifyCP->editData(searchO.indexs[0], editInput);
                cout << "\n" << editO.message << " Press enter to go back.\n";
            }
        }
        else {
            //existing cargo record has the max quantity already, cannot add new cargo
            cout << "Error: ID \"" << id << "\" already has maximum 10 cargo. Press enter to go back.\n";
        }
    }
}

void CargoUserInterface::importFilePrompt() {
    cout << "------------ Import Cargo Records from File ------------\n\n";
    cout << "Input file path to the Cargo data file:\n";
    cout << "If you have previously loaded records, they will be replaced.\nTo go back, type \"CANCEL\".\n\n-> ";
    string userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
    getline(cin, userInput);

    CargoDataAdder::addOutcome importO = addCP->importFromFile(userInput);
    cout << "\n" << importO.message << " Press enter to go back.\n";
}

void CargoUserInterface::exportFilePrompt() {
    cout << "------------ Exporting Cargo Records to File ------------\n\n";
    CargoDataDisplayer::dataValues isThereData = displayCP->getDataValues(0);
    if (isThereData.status == "NO_DATA") {
        cout << "There are no records. Add a new record or import from a file.\n";
        return;
    }

    //prompt for the file extension to export file
    cout << "Select a file extension to export:\n0) Cancel  1) .txt  2) .csv\n\n-> ";
    int fileformatChoice; cin >> fileformatChoice;
    if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

    //set the selected file extension
    DataExporter::exportOutcome canSetFileExtension;
    if (fileformatChoice == 0) { cout << "\nExporting is cancelled Press enter to go back.\n"; return; }
    if (fileformatChoice == 1) { canSetFileExtension = exportCP->setExportFileFormat("TXT"); }
    else if (fileformatChoice == 2) { canSetFileExtension = exportCP->setExportFileFormat("CSV"); }
    else { canSetFileExtension = exportCP->setExportFileFormat(""); } //wrong option so default blank

    //if file extension is set successfully, export the data to file
    if (canSetFileExtension.status == "SUCCESS") {
        cout << "Enter filename to export to (without \".csv\" or \".txt\"): ";
        string filename;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
        getline(cin, filename);
        DataExporter::exportOutcome exportO = exportCP->exportToFile(filename);
        cout << "\n" << exportO.message << " Press enter to go back.\n";
    }
    else if (canSetFileExtension.status == "ERROR") {
        cout << "Error: " << canSetFileExtension.message << "; invalid selected option." << endl;
    }
}

void CargoUserInterface::editCargoPrompt() {
    cout << "------ Edit Existing Cargo Record ------\n\n";
    cout << "Enter the ID you wish to edit.\n";
    cout << "To go back, type \"CANCEL\".\n\n-> ";
    string userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
    getline(cin, userInput);

    //try to find Cargo with the ID first
    DataDisplayer::searchOutcome searchO = displayCP->searchData(userInput);
    if (searchO.status == "CANCELLED") { cout << "\nEdit Cargo is cancelled. Press enter to go back.\n"; }
    else if (searchO.status == "DATA_NOT_FOUND") { cout << "Error: Empty input or the ID \"" << userInput << "\" does not exist. Press enter to go back.\n"; }

    else if (searchO.status == "DATA_FOUND" && searchO.indexs.size() == 1) {
        //show user the current record details, and prompt user to type new values for the Cargo record. 
        //if any attribute is unchanged, put a blank
        DataDisplayer::dataValues dv = displayCP->getDataValues(searchO.indexs[0]);
        cout << "\nThe original record is:\n";
        cout << "Destination: " << dv.destination << "; Time: " << dv.time << "; Quantity: " << dv.extraVal1 << ".\n\n";
        cout << "Enter the new destination, time and quantity, separated with a comma in between.\n";
        cout << "Leave the value blank if there are no changes. To go back, type \"CANCEL\".\n\n-> ";
        getline(cin, userInput);

        DataModifier::modifyOutcome editO = modifyCP->editData(searchO.indexs[0], userInput);
        cout << "\n" << editO.message << " Press enter to go back.\n";
    }
}

void CargoUserInterface::deleteCargoPrompt() {
    cout << "------ Delete Existing Cargo Record ------\n\n";
    cout << "Enter the ID you wish to delete.\n";
    cout << "To go back, type \"CANCEL\".\n\n-> ";
    string userInput; char deleteYesNo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
    getline(cin, userInput);

    //try to find Cargo with the ID first
    DataDisplayer::searchOutcome searchO = displayCP->searchData(userInput);
    if (searchO.status == "CANCELLED") { cout << "\nDelete Cargo is cancelled. Press enter to go back.\n"; }
    else if (searchO.status == "DATA_NOT_FOUND") { cout << "Error: Empty input or the ID \"" << userInput << "\" does not exist. Press enter to go back.\n"; }

    else if (searchO.status == "DATA_FOUND" && searchO.indexs.size() == 1) {
        //ID exists, show user the current record details 
        //if quantity is more than 1, prompt user to remove if desired
        DataDisplayer::dataValues dv = displayCP->getDataValues(searchO.indexs[0]);
        int oldQuantity = stoi(dv.extraVal1); //dont need try catch because the quantity is confirmed a number due to validation

        cout << "\nThe record values for the ID are:\n";
        cout << "Destination: " << dv.destination << "; Time: " << dv.time << "; Quantity: " << dv.extraVal1 << ".\n\n";

        if (oldQuantity > 1) {
            cout << "\nWould you like to remove some quantity? Enter quantity to remove." <<
                    "\nOr enter exact original quantity to delete whole record, or enter 0 to cancel.\n";
            cout << "Note that if you enter a negative number, it will become positive automatically.\n-> ";

            int removeQuantity; cin >> removeQuantity;
            if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }
            if (removeQuantity == 0) { cout << "\nAppend cargo cancelled. Press enter to go back.\n"; return; }

            int updatedQuantity = oldQuantity - abs(removeQuantity);
            if (updatedQuantity < 0) { cout << "Error: updated quantity must be minimally 1. Press enter to go back.\n"; }
            else {
                //if additional quantity is acceptable, edit that particular data with only quantity changed.
                string editInput = ", , " + to_string(updatedQuantity);
                DataModifier::modifyOutcome editO = modifyCP->editData(searchO.indexs[0], editInput);
                cout << "\n" << editO.message << " Press enter to go back.\n";
            }
        }
        else {
            //existing cargo record only has one exact quantity. ask to confirm delete
            cout << "\nAre you sure you want to delete this record? (Y/N): ";
            cin >> deleteYesNo;

            if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

            DataModifier::modifyOutcome deleteO = modifyCP->deleteData(searchO.indexs[0], deleteYesNo);
            cout << "\n" << deleteO.message << " Press enter to go back.\n";
        }
    }
}

void CargoUserInterface::displayCargo() {
    cout << "------ Displaying Cargo Records ------\n\n";
    CargoDataDisplayer::dataValues isThereData = displayCP->getDataValues(0);
    if (isThereData.status == "NO_DATA") {
        cout << "There are no records. Add a new record or import from a file.\n";
        return;
    }

    cout << "ID\tDestination\tTime\tCargo quantity\n";
    int index = 0; DataDisplayer::dataValues dv = displayCP->getDataValues(index);

    while (dv.status != "NO_DATA") {
        cout << dv.id << "\t";

        if (dv.destination.length() <= 7) { cout << dv.destination << "\t\t"; }
        else { cout << dv.destination << "\t"; }

        cout << dv.time << "\t"; cout << dv.extraVal1 << "\n"; //quantity is under extra value 1

        dv = displayCP->getDataValues(++index); //increment index and then get the next data value
    }
    cout << "\nAll Cargo data is displayed! ";
}

/* test main code
int main() {
    CargoDataPool cp;
    CargoUserInterface cInterface(cp);
    cInterface.showMenu();

    return 0;
}
*/
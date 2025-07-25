/*
Created by: Ong Kok Peng (2403435)
Date: 13/7/2025
*/

#include <iostream>
#include <string>
using namespace std;

#include "FreightUserInterface.h"

FreightUserInterface::FreightUserInterface() {
	addFP = new FreightDataAdder(fp);
	modifyFP = new FreightDataModifier(fp);
	displayFP = new FreightDataDisplayer(fp);
	exportFP = new FreightDataExporter(*displayFP);
}

void FreightUserInterface::waitForKey() {
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Press enter to continue...\n";
	cin.get();
}

void FreightUserInterface::clearScreen() {
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#endif
}

void FreightUserInterface::showMenu() {
    while (true) {
        int option;

        clearScreen();
        cout << "------- Menu for Freight: Please select an option ---------\n";
        cout << "1. Open/re-open Freight records file\n";
        cout << "2. Display Freight records.\n";
        cout << "3. Add Freight record.\n";
        cout << "4. Delete Freight record.\n";
        cout << "5. Edit Freight record.\n";
        cout << "6. Save Freight records to a new file\n";
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
            clearScreen(); importFilePrompt(); waitForKey(); //import freight data
            break;
        case 2:
            clearScreen(); displayFreight(); waitForKey(); //display freight data
            break;
        case 3:
            clearScreen(); addFreightPrompt(); waitForKey(); //add freight data
            break;
        case 4:
            clearScreen(); deleteFreightPrompt(); waitForKey(); //delete freight data
            break;
        case 5:
            clearScreen(); editFreightPrompt(); waitForKey(); //edit freight data
            break;
        case 6:
            clearScreen(); exportFilePrompt(); waitForKey(); //export freight data
            break;
        default:
            cout << "\nInvalid option, please type any number from 1 to 6.\n";
            waitForKey();
        }
    }
}

void FreightUserInterface::addFreightPrompt() {
	cout << "------ Adding New Freight Record ------\n\n";
	cout << "Enter the ID, destination, time and name, separated with a comma in between.\n";
	cout << "To go back, type \"CANCEL\".\n\n-> ";
	string userInput;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
	getline(cin, userInput);

	FreightDataAdder::addOutcome addO = addFP->addData(userInput);
	cout << "\n" << addO.message << " Press enter to go back.\n";
}

void FreightUserInterface::importFilePrompt() {
    cout << "------------ Import Freight Records from File ------------\n\n";
    cout << "Input file path to the Freight data file:\n";
    cout << "If you have previously loaded records, they will be replaced.\nTo go back, type \"CANCEL\".\n\n-> ";
    string userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
    getline(cin, userInput);

    FreightDataAdder::addOutcome importO = addFP->importFromFile(userInput);
    cout << "\n" << importO.message << " Press enter to go back.\n";
}

void FreightUserInterface::exportFilePrompt() {
    cout << "------------ Exporting Freight Records to File ------------\n\n";
    FreightDataDisplayer::dataValues isThereData = displayFP->getDataValues(0);
    if (isThereData.status == "NO_DATA") {
        cout << "There are no records. Add a new record or import from a file.\n";
        return;
    }

    //prompt for the file extension to export file
    cout << "Select a file extension to export:\n";
    cout << "0) Cancel  1) .txt  2) .csv\n\n-> ";
    int fileformatChoice; cin >> fileformatChoice;
    if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

    //set the selected file extension
    DataExporter::exportOutcome canSetFileExtension;
    if (fileformatChoice == 0) { cout << "\nExporting is cancelled Press enter to go back.\n"; return; }
    if (fileformatChoice == 1) { canSetFileExtension = exportFP->setExportFileFormat("TXT"); }
    else if (fileformatChoice == 2) { canSetFileExtension = exportFP->setExportFileFormat("CSV"); }
    else { canSetFileExtension = exportFP->setExportFileFormat(""); } //wrong option so default blank

    //if file extension is set successfully, export the data to file
    if (canSetFileExtension.status == "SUCCESS") {
        cout << "Enter filename to export to (without \".csv\" or \".txt\"): ";
        string filename;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
        getline(cin, filename);
        DataExporter::exportOutcome exportO = exportFP->exportToFile(filename);
        cout << "\n" << exportO.message << " Press enter to go back.\n";
    }
    else if (canSetFileExtension.status == "ERROR") {
        cout << "Error: " << canSetFileExtension.message  << "; invalid selected option." << endl;
    }
}

void FreightUserInterface::editFreightPrompt() {
    cout << "------ Edit Existing Freight Record ------\n\n";
    cout << "Enter the ID you wish to edit.\n";
    cout << "To go back, type \"CANCEL\".\n\n-> ";
    string userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
    getline(cin, userInput);

    //try to find freight with the ID first
    DataDisplayer::searchOutcome searchO = displayFP->searchData(userInput);
    if (searchO.status == "CANCELLED") { cout << "\nEdit freight is cancelled. Press enter to go back.\n"; }
    else if (searchO.status == "DATA_NOT_FOUND") { cout << "Error: Empty input or the ID \"" << userInput << "\" does not exist. Press enter to go back.\n"; }
    
    else if (searchO.status == "DATA_FOUND" && searchO.indexs.size() == 1) {
        //show user the current record details, and prompt user to type new values for the freight record. 
        //if any attribute is unchanged, put a blank
        DataDisplayer::dataValues dv = displayFP->getDataValues(searchO.indexs[0]);
        cout << "\nThe original record is:\n";
        cout << "Destination: " << dv.destination << "; Time: " << dv.time << "; Name: " << dv.extraVal1 << ".\n\n";
        cout << "Enter the new destination, time and name, separated with a comma in between.\n";
        cout << "Leave the value blank if there are no changes. To go back, type \"CANCEL\".\n\n-> ";
        getline(cin, userInput);

        DataModifier::modifyOutcome editO = modifyFP->editData(searchO.indexs[0], userInput);
        cout << "\n" << editO.message << " Press enter to go back.\n";
    }
}

void FreightUserInterface::deleteFreightPrompt() {
    cout << "------ Delete Existing Freight Record ------\n\n";
    cout << "Enter the ID you wish to delete.\n";
    cout << "To go back, type \"CANCEL\".\n\n-> ";
    string userInput; char deleteYesNo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline before the user input
    getline(cin, userInput);

    //try to find freight with the ID first
    DataDisplayer::searchOutcome searchO = displayFP->searchData(userInput);
    if (searchO.status == "CANCELLED") { cout << "\nDelete freight is cancelled. Press enter to go back.\n"; }
    else if (searchO.status == "DATA_NOT_FOUND") { cout << "Error: Empty input or the ID \"" << userInput << "\" does not exist. Press enter to go back.\n"; }

    else if (searchO.status == "DATA_FOUND" && searchO.indexs.size() == 1) {
        // show user the current record details and prompt user to confirm the delete
        DataDisplayer::dataValues dv = displayFP->getDataValues(searchO.indexs[0]);
        cout << "\nThe original record is:\n";
        cout << "Destination: " << dv.destination << "; Time: " << dv.time << "; Name: " << dv.extraVal1 << ".\n\n";
        cout << "Are you sure you want to delete this record? (Y/N): ";
        cin >> deleteYesNo;

        if (cin.fail()) { cout << "\nError: invalid input. Press enter to go back.\n"; return; }

        DataModifier::modifyOutcome deleteO = modifyFP->deleteData(searchO.indexs[0], deleteYesNo);
        cout << "\n" << deleteO.message << " Press enter to go back.\n";
    }
}

void FreightUserInterface::displayFreight() {
	cout << "------ Displaying Freight Records ------\n\n";
	FreightDataDisplayer::dataValues isThereData = displayFP->getDataValues(0);
	if (isThereData.status == "NO_DATA") {
		cout << "There are no records. Add a new record or import from a file.\n";
		return;
	}

    cout << "ID\tDestination\tTime\tFreight Name\n";
	int index = 0; DataDisplayer::dataValues dv = displayFP->getDataValues(index);

	while (dv.status != "NO_DATA") {
        cout << dv.id << "\t";

        if (dv.destination.length() <= 7) { cout << dv.destination << "\t\t"; }
        else { cout << dv.destination << "\t"; }

        cout << dv.time << "\t";

        cout << dv.extraVal1 << "\n"; //name is under extra value 1

		dv = displayFP->getDataValues(++index); //increment index and then get the next data value
	}
    cout << "\nAll freight data is displayed! ";
}

/* test main code
int main() {
	FreightUserInterface fInterface;
    fInterface.showMenu();

	return 0;
}
*/
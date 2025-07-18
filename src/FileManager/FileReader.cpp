/*
Created by: Chia Boon Pin (2403120)
Date: 17/7/2025
*/

#include "FileReader.h"
#include <string>
#include <fstream>

FileReader::FileReader(const std::string& filename) :
    _inputFile(filename), inputFile(_inputFile) {
    if (!inputFile.is_open()) { fileOpened = false; }
    else { fileOpened = true; }
}

bool FileReader::isFileOpened() { return fileOpened; }

std::string FileReader::readLine() {
    std::string fileLine;
    if (std::getline(inputFile, fileLine)) {
        if (fileLine.empty()) { return "blank line"; }
        else { return fileLine; }
    }
    else { 
        if (inputFile.is_open()) { inputFile.close(); }
        return "EOF";  
    }
}
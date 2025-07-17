/*
Created by: Chia Boon Pin (2403120)
Date: 17/7/2025
*/

#include "FileReader.h"
#include <fstream>

FileReader::FileReader() { fileLines = {}; }

bool FileReader::readFile(const std::string& filename) {
    
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        //empty or invalid file path; unable to locate file to open
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            fileLines.push_back(line);
        }
    }

    inFile.close();
    //check if any lines were captured

    if (fileLines.size() > 0) { return true; }
    else { return false; }
}

int FileReader::getLineCount() { return fileLines.size(); }

std::string FileReader::getFileLine(int lineNumber) { return fileLines[lineNumber]; }
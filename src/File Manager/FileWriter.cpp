/*
Created by: Chia Boon Pin (2403120)
Date: 17/7/2025
*/

#include <string>
#include "FileWriter.h"

FileWriter::FileWriter(const std::string& filename, bool append) : 
    _outputFile(filename, std::ios::out | (append ? std::ios::app : std::ios::trunc)), outputFile(_outputFile) {
    if (!outputFile.is_open()) { fileOpened = false; }
    else { fileOpened = true; }
}

bool FileWriter::isFileOpened() { return fileOpened; }

bool FileWriter::writeLine(std::string content) {
    outputFile << content;
    return true;
}

void FileWriter::closeFile() {
    if (outputFile.is_open()) { outputFile.close(); }
}
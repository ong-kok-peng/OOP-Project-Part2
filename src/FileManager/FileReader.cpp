#include "FileReader.h"
#include <fstream>

FileReader::FileReader() {}

FileReader::~FileReader() {}

std::vector<std::string> FileReader::readFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        return lines;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }

    inFile.close();
    return lines;
}
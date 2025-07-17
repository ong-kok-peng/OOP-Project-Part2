#pragma once
#include <string>
#include <vector>
/*
Created by: Chia Boon Pin (2403120)
Date: 17/7/2025
*/

class FileReader {
private:
    std::vector<std::string> fileLines;
public:
    FileReader();

    bool readFile(const std::string& filename);
    int getLineCount();
    std::string getFileLine(int lineNumber);
};
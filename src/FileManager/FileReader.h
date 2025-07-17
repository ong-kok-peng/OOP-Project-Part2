#pragma once
#include <string>
#include <vector>
/*
Created by: Chia Boon Pin (2403120)
Date: 17/7/2025
*/

class FileReader {
public:
    FileReader();
    ~FileReader();

    std::vector<std::string> readFile(const std::string& filename);
};
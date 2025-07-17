#pragma once
#include <string>
#include <vector>

class FileReader {
public:
    FileReader();
    ~FileReader();

    std::vector<std::string> readFile(const std::string& filename);
};
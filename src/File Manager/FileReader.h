/*
Created by: Chia Boon Pin (2403120)
Date: 17/7/2025
*/

#include <fstream>

class FileReader
{
    std::ifstream _inputFile;   // real stream object
    std::ifstream& inputFile;   // alias reference
    bool fileOpened;

public:
    explicit FileReader(const std::string& filename);
    ~FileReader() = default;

    FileReader(const FileReader&) = delete;
    FileReader& operator=(const FileReader&) = delete;

    FileReader(FileReader&&) noexcept = default;
    FileReader& operator=(FileReader&&) noexcept = default;

    bool isFileOpened();

    std::string readLine();
};
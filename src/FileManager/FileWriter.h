/*
Created by: Chia Boon Pin (2403120)
Date: 17/7/2025
*/

#include <fstream>

class FileWriter
{
    std::ofstream _outputFile;   // real stream object
    std::ofstream& outputFile;   // alias reference
    bool fileOpened;

public:
    explicit FileWriter(const std::string& filename, bool append);
    ~FileWriter() = default;

    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;

    FileWriter(FileWriter&&) noexcept = default;
    FileWriter& operator=(FileWriter&&) noexcept = default;

    bool isFileOpened();

    bool writeLine(std::string content);  

    void closeFile();
};
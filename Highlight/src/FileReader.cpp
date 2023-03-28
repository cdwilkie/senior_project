#include "../include/FileReader.h"
#include <fstream>
#include <iostream>

std::vector<std::wstring> FileReader::readLines(const std::string& filename) {
    std::vector<std::wstring> lines;
    std::wifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return lines;
    }
    std::wstring line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
} 
#pragma once

#include <string>
#include <vector>

class FileReader {
public:
    static std::vector<std::wstring> readLines(const std::string& filename);

};

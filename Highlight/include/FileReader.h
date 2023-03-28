/*
* FileReader class supports UTF-8 text source actions.
*/
#pragma once

#include <string>
#include <vector>

class FileReader {
public:
    /* readLines() static function accepts string filename as parameter.
    * Builds std::vector<std::wstring> to hold contents of each line
    * from text source. Returns the std::vector<std::wstring>
    */
    static std::vector<std::wstring> readLines(const std::string& filename);

};//end FileReader

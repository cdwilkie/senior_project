/*
* FileHandler class supports UTF-8 text source actions.
*/
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Tokenizer.h"

class FileHandler {
public:
    /* readLines() static function accepts string filename as parameter.
    * Builds std::vector<std::wstring> to hold contents of each line
    * from text source. Returns the std::vector<std::wstring>
    */
    static std::vector<std::wstring> readLines(const std::string& filename);

    static std::unordered_map<std::wstring, std::wstring> readKeyValues(
            const std::string& filename);

    static void writeToHtml(const std::string& filename,
            const std::vector<std::vector<Tokenizer::Token>>& tokens);

private:
   static std::wstring escapeHtml(const std::wstring& input);

};//end FileHandler

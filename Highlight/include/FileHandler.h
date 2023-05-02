/*
* FileHandler class supports wide char (Unicode) file
* functionality for reading in Unicode-containing files
* and writing to html the contents text source. Functionality
* to build key-value maps from read files.
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

    /* readKeyValues() populates an unordered map with an expected
    * Unicode string 'key' and the related Unicode string 'value',
    * collected from a .txt source. Returns unordered_map
    */
    static std::unordered_map<std::wstring, std::wstring> readKeyValues(
            const std::string& filename);

    /* writeToHtml() writes the contents of the passed vector
    * into an html file, specified in source.
    */
    static void writeToHtml(const std::string& filename,
            const std::vector<std::vector<Tokenizer::Token>>& tokens);

private:

   /* _escapeHtml is helper function to escape problematic
   * characters in string so that contents can be correctly
   * parsed in HTML. Returns wstring.
   */
   static std::wstring _escapeHtml(const std::wstring& input);

};//end FileHandler

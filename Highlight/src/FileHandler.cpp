/*
* FileHandler class supports reading UTF-8 encoded
* files. 
*/
#include "../include/FileHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>




/* readLines() accepts string filename to instantiate
* std::wifstream file object. Builds std::vector<std::wstring> "lines"
* to store the contents of each line from the text source. 
* Iterates through each line of text source with std::getline() 
* and appends each found line as new index in lines vector. 
* Returns lines vector.
*/
std::vector<std::wstring> FileHandler::readLines(const std::string& filename) {
    std::vector<std::wstring> lines;            //Vector to hold all unicode lines of text
    std::wifstream file(filename);              //Open filestream for unicode with filename
    if (!file || !file.is_open()) {             //If file can't be opened
        throw std::runtime_error("Failed to open file " + filename); //Throw error
        return lines;                           //Return the empty vector
    }//end if file error
    std::wstring line;                          //Build wstring to hold a unicode line text
    while (std::getline(file, line)) {          //While lines in textsource
        lines.push_back(line);                  //Add extracted line to lines vector
    }//end while lines
    file.close();
    return lines;                               //Return the populated vector
}

std::unordered_map<std::wstring, std::wstring> FileHandler::readKeyValues(
        const std::string& filename) {
    std::unordered_map<std::wstring, std::wstring> keyValues;
    std::wifstream file(filename);

    if (!file || !file.is_open()) {
        throw std::runtime_error("Failed to open file " + filename);
        return keyValues;
    }
    std::wstring line;
    while (std::getline(file, line)) {
        std::wistringstream wiss(line);
        std::wstring key, value;
        if (std::getline(wiss, key, L'"') && std::getline(wiss, key, L'"') &&
            std::getline(wiss, value, L'"') && std::getline(wiss, value, L'"')){
            keyValues[key] = value;
        }
    }
    file.close();
    return keyValues;
}

void FileHandler::writeToHtml(const std::string& filename,
        const std::vector<std::vector<Tokenizer::Token>>& tokens) {

    std::wofstream file(filename);
    if (!file.is_open() || !file) {
        throw std::runtime_error("Faild to open file " + filename);
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n"
        << "<meta charset=\"UTF-8\">\n<title>Output</title>\n</head>\n<body>\n";

    for (int i = 0; i < tokens.size(); ++i) {
        for (int j = 0; j < tokens[i].size(); ++j) {
 
            if (tokens[i][j].tokenID == 200) {
                file << "<span style=\"font-weight:bold;\">";
                file << tokens[i][j].word << L" ";
                file << "</span>";
            }

            else {
                file << "<span>";
                file << tokens[i][j].word << L" ";
                file << "</span>";
            }
        }
        file << "<br>\n";
    }
    file << "</body>\n</html>";
    file.close();
    std::cout << "Lines written successfully to " << filename << std::endl;

}

std::wstring FileHandler::_escapeHtml(const std::wstring& word) {
    std::wstring output;
    output.reserve(word.size());
    for (const auto& symbol : word) {
        switch (symbol) {
            case '<': 
                output += L"&lt;";
                break;
        }
    }
    return output;
}
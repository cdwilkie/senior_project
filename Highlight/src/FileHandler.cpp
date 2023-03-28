/*
* FileHandler class supports reading UTF-8 encoded
* files. 
*/
#include "../include/FileHandler.h"
#include <fstream>
#include <iostream>

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
    if (!file || !file.is_open()) {                                //If file can't be opened
        throw std::runtime_error("Failed to open file " + filename); //Throw error
        return lines;                           //Return the empty vector
    }//end if file error
    std::wstring line;                          //Build wstring to hold a unicode line text
    while (std::getline(file, line)) {          //While lines in textsource
        lines.push_back(line);                  //Add extracted line to lines vector
    }//end while lines
    return lines;                               //Return the populated vector
}

void FileHandler::writeLines(const std::string& filename, 
                const std::vector<std::wstring>& lines) {
    std::wofstream file(filename);
    if (!file.is_open() || !file) {
        throw std::runtime_error("Faild to open file " + filename);
    }
    for (int i = 0; i < lines.size(); ++i) {
        file << lines[i] << std::endl;
    }

}
/*
* FileHandler class supports wide char (Unicode) file
* functionality for reading in Unicode-containing files
* and writing to html the contents text source. Functionality
* to build key-value maps from read files.
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
    std::cout<<"\nLines Read Successfully from " << filename << std::endl;
    return lines;                               //Return the populated vector
}//end readLines

/* readKeyValues() accepts a string file pathname 
* and opens a file stream with that location. Reads each
* line and parses the line to extract a key and value,
* where each line of the source is expected to have a key
* enclosed in quotes and a value enclosed in quotes, i.e.
* ("key" "value"). Keys with no known value should be
* associated as "null" in the .txt source. Returns unordered_map
*
*/
std::unordered_map<std::wstring, std::wstring> FileHandler::readKeyValues(
        const std::string& filename) {
    std::unordered_map<std::wstring, std::wstring> keyValues;//Holds parsed data
    std::wifstream file(filename);              //Opens unicode compatible file stream

    if (!file || !file.is_open()) {             //If error opening file
        throw std::runtime_error("Failed to open file " + filename);//throw error
        return keyValues;                       //return map and exit func
    }//end if error opening
    std::wstring line;                          //Contents of current line
    while (std::getline(file, line)) {          //While lines in source
        std::wistringstream wiss(line);         //Unicode compatible string stream
        std::wstring key, value;                //Will hold extracted key and value
        if (std::getline(wiss, key, L'"') && std::getline(wiss, key, L'"') &&
            std::getline(wiss, value, L'"') && std::getline(wiss, value, L'"')){
            keyValues[key] = value;             //If correct format, extract and add key/value
        }//end if correct format
    }//end while lines
    file.close();                               //Close file stream
    std::cout<<"Lines Read Successfully from - " << filename << std::endl;
    return keyValues;                           //Return map
}//end readKeyValues

/*writeToHtml() opens a wide file stream, specified by the passed
* parameter and iterates through the passed vector to write its
* contents to file, encoded in HTML.
*
*/
void FileHandler::writeToHtml(const std::string& filename,
        const std::vector<std::vector<Tokenizer::Token>>& tokens) {

    std::wofstream file(filename);              //Opens unicode compatible file stream
    if (!file.is_open() || !file) {             //If error opening file
        throw std::runtime_error("Faild to open file " + filename);//throw error
    }//end if error opening file

    file << "<!DOCTYPE html>\n<html>\n<head>\n" //Write HTML header contents to file
        << "<meta charset=\"UTF-8\">\n<title>Search Results</title>\n</head>\n<body>\n";

    for (int i = 0; i < tokens.size(); ++i) {   //Iterate through vector
        for (int j = 0; j < tokens[i].size(); ++j) {//Iterate through every token
 
            if (tokens[i][j].tokenID == 200) {  //If token matches (id = 200)
                file << "<span style=\"font-weight:bold;\">";//Bold the contents
                file << tokens[i][j].word << L" ";//Token contents with unicode space
                file << "</span>";              //Close the bold contents
            }//end if token contents match

            else {                              //Else token is regular (no match)
                file << "<span>";               //Enclose contents regular text
                file << tokens[i][j].word << L" ";//Contents with unicode space
                file << "</span>";              //Close regular contents
            }//end else token regular not match
        }//end for every token
        file << "<br>\n";                       //Insert newline into HTML file
    }//end for entire vector
    file << "</body>\n</html>";                 //Close tags of HTML file
    file.close();                               //Close file
    std::cout << "Lines written successfully to " << filename << std::endl;//Confirmation
}//end writeToHtml()

/*_escapeHtml() is a helper function for writeToHtml() that
* escapes characters that could be interpreted as markup, etc.
*
*/
std::wstring FileHandler::_escapeHtml(const std::wstring& word) {
    std::wstring output;                        //Holds escaped data
    output.reserve(word.size());                //Resizes the container to size
    for (const auto& symbol : word) {           //Iterate through each char in word
        switch (symbol) {                       //Check different possible symbols
            case '<':                           //Matches < symbol
                output += L"&lt;";              //Escape symbol and concat to output
                break;                          //exit switch
        }//end switch symbol
    }//end for every char
    return output;                              //return escaped data
}//end _escapeHtml()
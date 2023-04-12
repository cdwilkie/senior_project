#include <iostream>
#include "../include/FileHandler.h"
#include "../include/UserInput.h"
#include "../include/Tokenizer.h"
#include "../include/SearchHandler.h"


int main (int argc, char** argv) {

    std::vector<std::wstring> lines;            //Holds file contents, one line per index
    
    if (argc <= 1) {                            //If no arguments given
        std::string inFile = UserInput::getFilename();//Prompt user for filename
       
        lines = FileHandler::readLines(inFile); //Open file and read lines

    }//end if no argument
    else {                                      //Else argument given 
        lines = FileHandler::readLines(argv[1]);//Use argument as filename, open, readlines
    }//end if argument
    

    std::vector<std::vector<Tokenizer::Token>> fileTokens;//2-D Holds tokens from each line

    size_t numThreads = 4;
    Tokenizer::tokenizeLines(lines, fileTokens, numThreads);

    lines.clear(); //Empty the lines vector
    lines.shrink_to_fit(); //Release memory from lines vector

    /*
    std::string filename = "../data/prefix.txt";

    std::unordered_map<std::wstring, std::wstring> keyValues = FileHandler::readKeyValues(filename);
    
    for (auto iter = keyValues.begin(); iter != keyValues.end(); ++iter) {
        const std::wstring& key = iter->first;
        const std::wstring& value = iter->second;
        std::wcout << key << L" : " << value << std::endl;
    };
    */
    
    SearchHandler::searchTokens(fileTokens, 4);
    
    
    std::string outFile = UserInput::getFilename();//Prompt for outfile location
    FileHandler::writeLines(outFile, fileTokens);    //Write lines to outfile
    

    return 0;
}
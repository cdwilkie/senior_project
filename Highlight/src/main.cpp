#include <iostream>
#include "../include/FileHandler.h"
#include "../include/UserInput.h"
#include "../include/Tokenizer.h"
#include "../include/SearchHandler.h"

#include "../include/UnitTest.h"


int main (int argc, char** argv) {

    auto start = UnitTest::start();//Test start

    std::vector<std::wstring> lines;            //Holds file contents, one line per index
    
    if (argc <= 1) {                            //If no arguments given
        std::string inFile = UserInput::getFilename();//Prompt user for filename
       
        lines = FileHandler::readLines(inFile); //Open file and read lines

    }//end if no argument
    else {                                      //Else argument given 
        lines = FileHandler::readLines(argv[1]);//Use argument as filename, open, readlines
    }//end if argument
    

    std::vector<std::vector<Tokenizer::Token>> fileTokens;//2-D Holds tokens from each line

    size_t numThreads = 8;
    Tokenizer::tokenizeLines(lines, fileTokens, numThreads);

    //std::vector<std::wstring>().swap(lines);
    
    /*
    lines.clear(); //Empty the lines vector
    lines.shrink_to_fit(); //Release memory from lines vector
    */

    /*
    std::string filename = "../data/prefix.txt";

    std::unordered_map<std::wstring, std::wstring> keyValues = FileHandler::readKeyValues(filename);
    
    for (auto iter = keyValues.begin(); iter != keyValues.end(); ++iter) {
        const std::wstring& key = iter->first;
        const std::wstring& value = iter->second;
        std::wcout << key << L" : " << value << std::endl;
    };
    */
    
    SearchHandler::searchTokens(fileTokens, 8);
    
    
    std::string outFile = "../data/outfile.html";//UserInput::getFilename();//Prompt for outfile location
    FileHandler::writeToHtml(outFile, fileTokens);    //Write lines to outfile
    
    auto stop = UnitTest::stop();
    UnitTest::duration(start,stop);
    return 0;
}
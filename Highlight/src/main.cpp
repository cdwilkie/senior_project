#include <iostream>
#include "../include/FileHandler.h"
#include "../include/UserInput.h"
#include "../include/Tokenizer.h"
#include "../include/SearchHandler.h"
#include "../include/UserInterface.h"

#include "../include/UnitTest.h"


int main (int argc, char** argv) {

    auto start = UnitTest::start();//Test start

    UserInterface::greetUser();                 //Greet User with Prompt

    std::vector<std::wstring> lines;            //Holds file contents, one line per index
    std::string inFile;
    
    if (argc <= 1) {                            //If no arguments given
        inFile = UserInput::getFilename();//Prompt user for filename
       
        lines = FileHandler::readLines(inFile); //Open file and read lines

    }//end if no argument
    else {                                      //Else argument given 
        inFile = argv[1];
        lines = FileHandler::readLines(inFile);//Use argument as filename, open, readlines
    }//end if argument
    

    std::vector<std::vector<Tokenizer::Token>> fileTokens;//2-D Holds tokens from each line

    size_t numThreads = 4;                      //Set desired thread count
    UserInterface::tokenizeStatus(inFile);      //Notify user of status
    Tokenizer::tokenizeLines(lines, fileTokens, numThreads);//Tokenize source

    UserInterface::searchingSource(inFile);     //Notify User of status    
    SearchHandler::searchTokens(fileTokens, numThreads);//Search tokens from source
    
    
    std::string outFile = "../results/results.html";//UserInput::getFilename();//Prompt for outfile location
    UserInterface::highlightWrite(outFile);     //Notify user of status
    FileHandler::writeToHtml(outFile, fileTokens);//Write lines to outfile
    
    auto stop = UnitTest::stop();
    UnitTest::duration(start,stop);
    UserInterface::programEnd();
    return 0;
}
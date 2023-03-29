#include "../include/FileHandler.h"
#include "../include/UserInput.h"
#include "../include/Tokenizer.h"


int main (int argc, char** argv) {

    std::vector<std::wstring> lines;            //Holds file contents, one line per index
    
    if (argc <= 1) {                            //If no arguments given
        std::string inFile = UserInput::getFilename();//Prompt user for filename
        lines = FileHandler::readLines(inFile); //Open file and read lines
    }//end if no argument
    else {                                      //Else argument given 
        lines = FileHandler::readLines(argv[1]);//Use argument as filename, open, readlines
    }//end if argument
    
    std::string outFile = UserInput::getFilename();//Prompt for outfile location
    FileHandler::writeLines(outFile, lines);    //Write lines to outfile

    //Test tokenizer
    std::vector<std::vector<std::wstring>> tokens;//2-D Holds tokens from each line

    for (int i = 0; i < lines.size(); ++i) {    //Iterate through each line
        tokens.push_back(Tokenizer::tokenize(lines[i]));//Tokenize each word and add to vector
    }//end for 

    return 0;
}
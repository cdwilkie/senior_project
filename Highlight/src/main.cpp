#include "../include/FileHandler.h"
#include "../include/UserInput.h"
#include "../include/Tokenizer.h"
#include <iostream>

int main (int argc, char** argv) {

    std::vector<std::wstring> lines;
    
    if (argc <= 1) {
        std::string inFile = UserInput::getFilename();
        lines = FileHandler::readLines(inFile);
    }
    else {
        lines = FileHandler::readLines(argv[1]);
    }
    
    std::string outFile = UserInput::getFilename();
    FileHandler::writeLines(outFile, lines);

    //Test tokenizer
    std::vector<std::vector<std::wstring>> tokens;
    for (int i = 0; i < lines.size(); ++i) {
        tokens.push_back(Tokenizer::tokenize(lines[i]));
        for (int j = 0; j < tokens[i].size(); ++j) {
            if (! (j == tokens[i].size()-1)) {
                std::wcout << tokens[i][j] << "  *  ";
            }
            else {
                std::wcout << tokens[i][j];
            }
        }
        std:: wcout << std::endl;
        
    }

    return 0;
}
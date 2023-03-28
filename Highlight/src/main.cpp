#include "../include/FileHandler.h"
#include "../include/UserInput.h"
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

    return 0;
}
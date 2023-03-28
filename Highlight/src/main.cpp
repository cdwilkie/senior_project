#include "../include/FileReader.h"
#include "../include/UserInput.h"
#include <iostream>

int main (int argc, char** argv) {
    if (argc <= 1) {
        std::string filename = UserInput::getFilename();
        auto lines = FileReader::readLines(filename);
    }
    else {
        auto lines = FileReader::readLines(argv[1]);
    }
    


    return 0;
}
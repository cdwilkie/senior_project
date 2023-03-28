#include "../include/FileReader.h"
#include "../include/UserInput.h"
#include <iostream>

int main () {
    std::string filename = UserInput::getFilename();
    auto lines = FileReader::readLines(filename);


    return 0;
}
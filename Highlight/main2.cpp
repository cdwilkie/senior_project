#include "FileReader.h"
#include <iostream>

int main () {
    std::string filename = "input.txt";
    auto lines = FileReader::readLines(filename);


    return 0;
}
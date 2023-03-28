#include "../include/FileReader.h"
#include <iostream>

int main () {
    std::string filename = "../data/input.txt";
    auto lines = FileReader::readLines(filename);


    return 0;
}
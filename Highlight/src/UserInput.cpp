#include "../include/UserInput.h"
#include <iostream>

std::string UserInput::getFilename() {
    std::string filename;
    std::cout << "Enter a filename: ";
    std::cin >> filename;
    return filename;
}
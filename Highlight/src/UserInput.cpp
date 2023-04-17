/* UserInput class supports collecting data
* from user via keyboard input
*/
#include "../include/UserInput.h"
#include <iostream>

/* UserInput::getFilename() creates a std::string filename
* to store collected filename input from user.
* Returns std::string filename
*/
std::string UserInput::getFilename() {
    std::string filename;                       //String to hold filename
    std::cout << "Enter a filename: ";          //Prompt user for filename
    std::cin >> filename;                       //Collect filename from input stream
    return filename;                            //Return filename string
}
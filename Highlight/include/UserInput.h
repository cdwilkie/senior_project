/* UserInput class supports collecting data
* from user via keyboard input / input stream
*/
#pragma once

#include <string>

class UserInput {
public:
    /*getFilename() encapsulates logic to
    * prompt user for the path of a file to use
    * Returns string pathname.
    */
    static std::string getFilename();

};
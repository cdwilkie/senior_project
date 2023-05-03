/*UnitTest encapsulates timing functionality
* in order to evaluate runtime performance
* of the program in various phases of operation.
* Supports a start, stop, and duration calcuation.
*/
#pragma once

#include <chrono>

class UnitTest {
public:
    /*start() establishes a time point to serve as the start time
    *Returns time_point
    */
    static std::chrono::time_point<std::chrono::high_resolution_clock> start();
    
    /*stop() establishes a time point to serve as the stop time
    * Returns a time_point
    */
    static std::chrono::time_point<std::chrono::high_resolution_clock> stop();
    
    /*duration() accepts a start and stop time and
    * calculates the amount of time that transpired
    * between the two time points
    */
    static void duration(std::chrono::time_point<std::chrono::high_resolution_clock> start,
        std::chrono::time_point<std::chrono::high_resolution_clock> stop);
};
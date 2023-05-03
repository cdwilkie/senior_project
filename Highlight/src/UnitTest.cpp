/*UnitTest provides timing functionality
* in order to test runtime of various
* program areas.
*/
#include "../include/UnitTest.h"
#include <iostream>


/*start() creates a time point object to serve 
* as a start point for runtime performance.
* Returns time_point
*/
std::chrono::time_point<std::chrono::high_resolution_clock> UnitTest::start() {
    return std::chrono::high_resolution_clock::now();
}//end start()

/*stop() creates a time point object to serve
* as a stop point for runtime performance.
* Returns time_point
*/
std::chrono::time_point<std::chrono::high_resolution_clock> UnitTest::stop() {
    return std::chrono::high_resolution_clock::now();
}//end stop()

/*duration() calculates the amount of elapsed
* time between the passed start and stop
* time_point objects. Outputs result to
* console in microseconds 1*10^-6 seconds
*/
void UnitTest::duration(std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::time_point<std::chrono::high_resolution_clock> stop) {
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds" << std::endl;
}//end duration()
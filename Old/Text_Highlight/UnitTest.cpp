#include "UnitTest.h"
#include <iostream>

std::chrono::time_point<std::chrono::high_resolution_clock> UnitTest::start() {
    return std::chrono::high_resolution_clock::now();
}

std::chrono::time_point<std::chrono::high_resolution_clock> UnitTest::stop() {
    return std::chrono::high_resolution_clock::now();
}

void UnitTest::duration(std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::time_point<std::chrono::high_resolution_clock> stop) {
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Elapsed time: " << elapsed.count() << " microseconds" << std::endl;
}
#pragma once

#include <chrono>

class UnitTest {
public:
    static std::chrono::time_point<std::chrono::high_resolution_clock> start();
    static std::chrono::time_point<std::chrono::high_resolution_clock> stop();
    static void duration(std::chrono::time_point<std::chrono::high_resolution_clock> start, std::chrono::time_point<std::chrono::high_resolution_clock> stop);
};
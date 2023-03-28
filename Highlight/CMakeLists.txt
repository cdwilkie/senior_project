cmake_minimum_required(VERSION 3.10)

project(highlight)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES src/main.cpp include/FileReader.h src/FileReader.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
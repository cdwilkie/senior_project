cmake_minimum_required(VERSION 3.10)

project(highlight)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp FileReader.h FileReader.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
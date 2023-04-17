cmake_minimum_required(VERSION 3.10)

project(highlight)


set(CMAKE_CXX_COMPILER "/usr/local/opt/gcc/bin/g++-12")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
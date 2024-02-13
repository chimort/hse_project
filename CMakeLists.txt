cmake_minimum_required(VERSION 3.10)

project(hwlib)

include(GoogleTest)
find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(hwlib main.cpp custom_long.h custom_long.cpp)

add_subdirectory(tests)
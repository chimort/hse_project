cmake_minimum_required(VERSION 3.10)

project(hwlib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(hwlib main.cpp custom_long.h custom_long.cpp)

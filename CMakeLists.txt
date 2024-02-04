cmake_minimum_required(VERSION 3.10)

project(hwlib)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)

add_executable(hwlib main.cpp custom_long.cpp)


install(TARGETS hwlib DESTINATION bin)
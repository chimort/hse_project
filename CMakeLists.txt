cmake_minimum_required(VERSION 3.10)

project(hwlib)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GoogleTest)
find_package(GTest REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(hwlib ${SOURCE_FILES})

include_directories(custom_long_lib)
add_subdirectory(custom_long_lib)

target_link_libraries(hwlib custom_long_lib)

add_subdirectory(tests)
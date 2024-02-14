project(Google_tests)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(my_tests my_tests.cpp)

target_link_libraries(my_tests custom_long_lib)

target_link_libraries(my_tests gtest gtest_main)
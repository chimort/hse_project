project(Google_tests)
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(my_tests my_tests.cpp ../custom_long.h ../custom_long.cpp)

target_link_libraries(my_tests ${SOURCE_DIR})

target_link_libraries(my_tests gtest gtest_main)
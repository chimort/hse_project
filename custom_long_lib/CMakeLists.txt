project(custom_long)

set(HEADER_FILES
    custom_long.h)

set(SOURCE_FILES custom_long.cpp)

add_library(custom_long_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
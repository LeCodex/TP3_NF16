cmake_minimum_required(VERSION 3.15)
project(TP3 C)

set(CMAKE_C_STANDARD 99)
file(GLOB HEADER_FILES include/*.h )
file(GLOB SOURCE_FILES src/*.c)
add_executable(TP3 ${HEADER_FILES} ${SOURCE_FILES})
find_library(TP3_lib TP3_provided HINTS lib)
target_link_libraries(TP3 ${TP3_lib})
cmake_minimum_required(VERSION 3.28)
project(AISD C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCES
        "Project/*.h"
        "Project/*.c"
)

add_executable(AISD ${SOURCES})
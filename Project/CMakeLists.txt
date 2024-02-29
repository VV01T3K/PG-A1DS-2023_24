cmake_minimum_required(VERSION 3.28)
project(Project C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCES
        "*.h"
        "*.c"
)

add_executable(Project ${SOURCES})
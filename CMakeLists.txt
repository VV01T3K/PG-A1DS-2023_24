cmake_minimum_required(VERSION 3.28)
project(OOP)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE  SOURCES
        "Project/*.h"
        "Project/*.cpp"
)

add_executable(OOP ${SOURCES})
cmake_minimum_required(VERSION 3.28)
project(AISD)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        "Project/*.h"
        "Project/*.cpp"
)

add_executable(AISD ${SOURCES})
cmake_minimum_required(VERSION 3.0)

project(convex_hull)

set(SOURCES
    test.cpp
)

add_executable(test ${SOURCES})

include_directories(
    "/usr/include/eigen3"
)
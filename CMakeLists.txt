cmake_minimum_required(VERSION 3.0)

project(convex_hull)

set(SOURCES
    point3d.cpp
    edge.cpp
    face.cpp
    convexHull.cpp
    test.cpp
)

add_executable(test ${SOURCES})

include_directories(
    "/usr/include/eigen3"
)
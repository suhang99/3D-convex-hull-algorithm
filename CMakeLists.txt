cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)

project(convex_hull)

find_package(Open3D HINTS ${CMAKE_INSTALL_PREFIX}/lib/CMake)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${Open3D_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Open3D_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${Open3D_EXE_LINKER_FLAGS}")

add_definitions(-DUNIX)
add_definitions(-O3)

set(SOURCES
    point3d.cpp
    edge.cpp
    face.cpp
    convexHull.cpp
    visualizer.cpp
    test_convexhull.cpp
)

set(SOURCES2
    point3d.cpp
    edge.cpp
    face.cpp
    convexHull.cpp
    visualizer.cpp
    test_performance.cpp
)

set(SOURCES3
    point3d.cpp
    edge.cpp
    face.cpp
    convexHull.cpp
    visualizer.cpp
    test_collision.cpp
)

link_directories(${Open3D_LIBRARY_DIRS})

add_executable(test_convexhull ${SOURCES})
add_executable(test_performance ${SOURCES2})
add_executable(test_collision ${SOURCES3})

include_directories(
    "/usr/include/eigen3"
)

target_link_libraries(test_convexhull
    PRIVATE
    ${Open3D_LIBRARIES}
)

target_include_directories(test_convexhull
    PUBLIC 
    ${Open3D_INCLUDE_DIRS}
)

target_link_libraries(test_performance
    PRIVATE
    ${Open3D_LIBRARIES}
)

target_include_directories(test_performance
    PUBLIC 
    ${Open3D_INCLUDE_DIRS}
)

target_link_libraries(test_collision
    PRIVATE
    ${Open3D_LIBRARIES}
)

target_include_directories(test_collision
    PUBLIC 
    ${Open3D_INCLUDE_DIRS}
)
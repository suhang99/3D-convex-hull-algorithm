# 3D-convex-hull-algorithm
Computer Graphics II: Implementation of a 3D convex hull algorithm

This is a pure C++ implementation of incremental convex hull algorithm

## Development Environment
- Ubuntu 20.04
- gcc 9.3.0

## Dependencies
- CMake
- Eigen
- Open3d

## Input data
This implementation will take point cloud as input. Supported types are
ply, pcd, txt

For txt file, each line should be only contain the xyz coordinate and there should not have empty line or other data. Look files under data folder for reference.

## Usage

Build executable
```
cd build && cmake .. && make
```
And you will see 3 executables under build folder

**test_convexhull** will compute the convex hull of given data and visualize.

Usage is
```
./test_convexhull ../data/bunny.ply
```
You can also add an extra argument (point, mesh, vertex) to specify the vislization type , default will be the convex hull. For example
```
./test_convexhull ../data/bunny.ply point
```

**test_collision** will take 2 pointcloud as input and check whether their convex hull collide or not.

Usage is
```
./test_collision ../data/random1.txt ../data/random2.txt
```
Similar to test_convexhull, you can also add an extra argument.

**test_performance** will record the running time with incremental number of points, and output txt which each line is the running time. Please see test_performance.cpp for more details.

Usage
```
./test_performance
```
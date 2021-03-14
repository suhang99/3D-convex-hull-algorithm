#include "convexHull.hpp"
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <random>
#include <open3d/Open3D.h>

using namespace std;
using namespace Eigen;
using namespace open3d::geometry;
using namespace open3d::visualization;


int main(){
    // vector<Vector3d> points;
    // points.push_back(Vector3d(1,-1,0));
    // points.push_back(Vector3d(-1,-1,0));
    // points.push_back(Vector3d(0,1,0));
    // points.push_back(Vector3d(0,0,1));
    // points.push_back(Vector3d(0,0,2));

    // IncrementalConvexHull convexhull(points);
    // convexhull.run();
    // convexhull.plot("convex hull");

    IncrementalConvexHull convexhull("../data/Copper key.ply");
    cout<<"read"<<endl;
    convexhull.run();
    convexhull.plot("convex hull");

    return 0;
}
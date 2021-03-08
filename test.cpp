#include "convexHull.hpp"
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <set>

using namespace std;
using namespace Eigen;

int main(){
    vector<Vector3d> points;
    points.push_back(Vector3d(1,-1,0));
    points.push_back(Vector3d(-1,-1,0));
    points.push_back(Vector3d(0,1,0));
    points.push_back(Vector3d(0,0,1));
    points.push_back(Vector3d(0,0,2));
    
    IncrementalConvexHull convexhull(points);
    convexhull.run();
    convexhull.printPoints();

    return 0;
}
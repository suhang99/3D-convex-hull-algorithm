// #include "convexHull.hpp"
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <set>

using namespace std;
using namespace Eigen;

int main(){
    set<int> s;
    s.insert(1);
    s.insert(2);

    auto i = s.find(1);

    cout<<*i<<endl;

    // vector<Point3d> points;
    // points.push_back(Point3d(0,0,0));
    // points.push_back(Point3d(0,0,1));
    // points.push_back(Point3d(0,1,0));
    // points.push_back(Point3d(1,0,0));
    // points.push_back(Point3d(0,1,1));
    // points.push_back(Point3d(1,0,1));
    // points.push_back(Point3d(1,1,0));
    // points.push_back(Point3d(1,1,1));

    // ConvexHull convexhull(points);
    // convexhull.printPoints();

    // convexhull.run();


    return 0;
}
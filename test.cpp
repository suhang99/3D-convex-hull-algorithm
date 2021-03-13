#include "convexHull.hpp"
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <random>
#include <open3d/Open3D.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace Eigen;
using namespace open3d::geometry;
using namespace open3d::visualization;
using namespace cv;


int main(){
    // f();
    // vector<Vector3d> points;
    // points.push_back(Vector3d(1,-1,0));
    // points.push_back(Vector3d(-1,-1,0));
    // points.push_back(Vector3d(0,1,0));
    // points.push_back(Vector3d(0,0,1));
    // points.push_back(Vector3d(0,0,2));

    // IncrementalConvexHull convexhull(points);
    // convexhull.run();
    // convexhull.printPoints();
    // convexhull.plot("convex hull");

    TriangleMesh mesh;
    mesh.CreateSphere(10);
    shared_ptr<TriangleMesh> mesh_ptr = make_shared<TriangleMesh>(mesh);
    DrawGeometries({mesh_ptr}, "sphere", 640, 480, 50, 50, false, true);

    return 0;
}
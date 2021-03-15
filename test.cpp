#include "convexHull.hpp"
#include "visualizer.hpp"
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <random>
#include <open3d/Open3D.h>
#include <limits>

using namespace std;
using namespace Eigen;
using namespace open3d::geometry;
using namespace open3d::visualization;

void test1(){
    cs271::Visualizer visualizer;
    vector<Vector3d> points1, points2;
    points1.push_back(Vector3d(0,0,0));
    points1.push_back(Vector3d(0,0,2));
    points1.push_back(Vector3d(0,2,0));
    points1.push_back(Vector3d(0,2,2));
    points1.push_back(Vector3d(2,0,0));
    points1.push_back(Vector3d(2,0,2));
    points1.push_back(Vector3d(2,2,0));
    points1.push_back(Vector3d(2,2,2));
    
    points2.push_back(Vector3d(3,0,0));
    points2.push_back(Vector3d(3,0,2));
    points2.push_back(Vector3d(3,2,0));
    points2.push_back(Vector3d(3,2,2));
    points2.push_back(Vector3d(5,0,0));
    points2.push_back(Vector3d(5,0,2));
    points2.push_back(Vector3d(5,2,0));
    points2.push_back(Vector3d(5,2,2));

    cs271::ConvexHull hull1(points1), hull2(points2);
    hull1.run();
    hull2.run();

    cout<<isCollide(hull1, hull2)<<endl;

    visualizer.plotHull(hull1);
    // visualizer.plotHull2(hull1, hull2);
}


void test2(){
    cs271::Visualizer visualizer;
    vector<Vector3d> points1;
    points1.push_back(Vector3d(0,0,0));
    points1.push_back(Vector3d(0,0,3));
    points1.push_back(Vector3d(0,1,3));
    points1.push_back(Vector3d(0,2,3));
    points1.push_back(Vector3d(0,3,3));
    points1.push_back(Vector3d(1,3,3));
    points1.push_back(Vector3d(2,3,4));
    points1.push_back(Vector3d(1,3,5));
    
    cs271::ConvexHull hull1(points1);
    hull1.run();

    visualizer.plotHull(hull1);

}

void test3(){
    cs271::Visualizer visualizer;
    cs271::ConvexHull hull("../data/test.txt");
    hull.run();
    hull.printFaces();
    visualizer.plotHull(hull);
}

int main(){
    // test1();
    // test2();
    test3();

    return 0;
}
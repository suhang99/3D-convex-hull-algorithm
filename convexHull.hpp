// CS271 Computer Graphics II Homework1
// Author: Su Hang
// Date  : 2021-03-06

#ifndef CS271_HW1_convexhull
#define CS271_HW1_convexhull

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <open3d/Open3D.h>
#include "point3d.hpp"
#include "edge.hpp"
#include "face.hpp"

using namespace std;
using namespace Eigen;

namespace cs271{


/* Implementation for incremental 3D convex hull algorithm */
class ConvexHull{
    friend class Visualizer;
    friend bool isCollide(ConvexHull&, ConvexHull&);

  public:
    ConvexHull(vector<Vector3d>);
    ConvexHull(const string);
    ~ConvexHull();
    void printPoints();
    void printFaces();
    void run();
    pair<Vector3d, Vector3d> getBoundingBox();
  
  private:
    vector<Point3d*> points;         /* all input points */
    vector<bool> flags;              /* Whether the point accessed or not */
    set<Point3d*> vertices;          /* all points of convex hull */
    set<Face*> faces;                /* all faces of convex hull */
    set<Edge*> edges;                /* all edges of convex hull */
    Point3d inner_point;             /* inner point of convex hull */

    void _init();
    Edge* _addEdge(Point3d*, Point3d*);
    Face* _addFace(Point3d*, Point3d*, Point3d*);
    void _removeFace(Face*);
    void _removeEdge(Edge*);
};

bool isCollide(ConvexHull&, ConvexHull&);

}

#endif
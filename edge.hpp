#ifndef CS271_HW1_edge
#define CS271_HW1_edge

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <set>

/* Declare classes here to avoid cross-reference */
class Point3d;
class Face;

class Edge{
  public:
    Point3d *p1, *p2;
    Face *f1, *f2;

    Edge();
    Edge(Point3d*, Point3d*);
};

Edge* getEdge(Point3d*, Point3d*);

#endif
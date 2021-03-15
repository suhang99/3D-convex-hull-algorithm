#ifndef CS271_HW1_face
#define CS271_HW1_face

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <set>


namespace cs271{

class Point3d;
class Edge;

class Face{
  public:
    Point3d *p1, *p2, *p3;
    Edge *e12, *e23, *e13;

    Face();
    Face(Point3d*, Point3d*, Point3d*);
};

double computeVolumn(Face*, Point3d*);
Vector3d projectPointToPlane(Face*, Point3d*);

}
#endif
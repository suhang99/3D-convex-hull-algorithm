#ifndef CS271_HW1_point3d
#define CS271_HW1_point3d

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <set>

namespace cs271{

using namespace std;
using namespace Eigen;

class Edge;

/* point in 3D */
class Point3d{
  public:
    Vector3d point;
    set<Edge*> edges;
    int id;

    Point3d() = default;
    Point3d(Vector3d);
    Point3d(Vector3d, int);

    friend ostream& operator<<(ostream& output, const Point3d& p){
        output<<"("<<p.point[0]<<","<<p.point[1]<<","<<p.point[2]<<")";
        return output;
    }
};

bool isColinear(Point3d*, Point3d*, Point3d*);
bool isCoplanar(Point3d*, Point3d*, Point3d*, Point3d*);

}
#endif
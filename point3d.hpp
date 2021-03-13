#ifndef CS271_HW1_point3d
#define CS271_HW1_point3d

#include <eigen3/Eigen/Dense>
#include <set>

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
};

#endif
#include "point3d.hpp"
#include "edge.hpp"

Point3d::Point3d(Vector3d _point):point(_point), id(-1){}

Point3d::Point3d(Vector3d _point, int _id):point(_point), id(_id){}
#include "point3d.hpp"
#include "edge.hpp"

namespace cs271{

Point3d::Point3d(Vector3d _point):point(_point), id(-1){}

Point3d::Point3d(Vector3d _point, int _id):point(_point), id(_id){}

bool
isColinear(Point3d *p1, Point3d *p2, Point3d *p3){
    Vector3d v12 = p2->point - p1->point;
    Vector3d v13 = p3->point - p1->point;
    return v12.cross(v13).norm() < 1e-9 ? true : false;
}

bool
isCoplanar(Point3d *p1, Point3d *p2, Point3d *p3, Point3d *p4){
    MatrixXd mat(4,4);
    mat << p1->point[0], p1->point[1], p1->point[2], 1,
           p2->point[0], p2->point[1], p2->point[2], 1,
           p3->point[0], p3->point[1], p3->point[2], 1,
           p4->point[0], p4->point[1], p4->point[2], 1;    
    return abs(mat.determinant()) < 1e-15 ? true : false;
}

}
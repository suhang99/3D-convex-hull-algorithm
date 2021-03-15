#include "point3d.hpp"
#include "edge.hpp"
#include "face.hpp"

namespace cs271{

Face::Face():p1(nullptr),p2(nullptr),p3(nullptr),e12(nullptr),e13(nullptr),e23(nullptr){}
Face::Face(Point3d *_p1, Point3d *_p2, Point3d *_p3):p1(_p1),p2(_p2),p3(_p3){}

/* Compute the volumn of tetrahedron formed by face and point */
double 
computeVolumn(Face *f, Point3d *p){
    MatrixXd mat(4,4);
    mat << f->p1->point[0], f->p1->point[1], f->p1->point[2], 1,
           f->p2->point[0], f->p2->point[1], f->p2->point[2], 1,
           f->p3->point[0], f->p3->point[1], f->p3->point[2], 1,
               p->point[0],     p->point[1],     p->point[2], 1;
    return mat.determinant();
}

Vector3d
projectPointToPlane(Face *face, Point3d *point){
    Vector3d normal = (face->p1->point - face->p2->point).cross(face->p1->point - face->p3->point);
    normal.normalize();
    Vector3d vec = point->point - face->p1->point;
    double distance = normal.dot(vec);
    return point->point - distance * normal;
}

}
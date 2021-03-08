#include "point3d.hpp"
#include "edge.hpp"
#include "face.hpp"

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
#ifndef CS271_HW1_geometry
#define CS271_HW1_geometry

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <set>

using namespace std;
using namespace Eigen;

/* point in 3D */
class Point3d{
  public:
    Vector3d point;
    set<Edge*> edges;

    Point3d(Vector3d _point):point(_point){
    }
};

/* Edge */
class Edge{
  public:
    Point3d *p1, *p2;
    Face *f1, *f2;

    Edge(Point3d *_p1, Point3d *_p2):p1(_p1),p2(_p2),f1(nullptr),f2(nullptr){
    }
};

/* Face in 3D */
class Face{
  public:
    Point3d *p1, *p2, *p3;
    Edge *e12, *e23, *e13;
    bool visible;

    Face(Point3d *_p1, Point3d *_p2, Point3d *_p3):p1(_p1),p2(_p2),p3(_p3){
        e12 = getEdge(p1, p2);
        e23 = getEdge(p2, p3);
        e13 = getEdge(p1, p3);
        visible = false;
    }
};

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

Edge*
getEdge(Point3d *p1, Point3d *p2){
    for(auto edge: p1->edges){
        if(edge->p1 == p2 || edge->p2 == p2){
            return edge;
        }
    }
    return nullptr;
}

#endif
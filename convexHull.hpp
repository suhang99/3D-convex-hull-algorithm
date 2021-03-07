#ifndef CS271_HW1_convexhull
#define CS271_HW1_convexhull

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <vector>
#include "geometry.hpp"

using namespace std;
using namespace Eigen;

/* Implementation for incremental 3D convex hull algorithm */
class ConvexHull{
  public:
    ConvexHull(vector<Vector3d>);
    ~ConvexHull();
    void printPoints();
    bool run();
  
  private:
    vector<Point3d*> points;         /* all input points */
    vector<Point3d*> vertice;        /* all points of convex hull */
    vector<Face*> faces;             /* all faces of convex hull */ 
    vector<Edge*> edges;             /* all edges of convex hull */
    vector<bool> flags;              /* Whether the point accessed or not */

    void _init();
    void _resetFacesVisibility();
    void _addFace(Point3d*, Point3d*, Point3d*, Point3d*);
};

/* Copy input points */
ConvexHull::ConvexHull(vector<Vector3d> pts){
    /* set all input points */
    points.resize(pts.size());
    for(int i = 0; i < pts.size(); i++){
        points[i] = new Point3d(pts[i]);        
    }
    /* set all points unexplored */
    flags.resize(pts.size());
    for(auto i = flags.begin(); i != flags.end(); i++){
        *i = false;
    }
}

ConvexHull::~ConvexHull(){
    // TODO: 
    ;
}

/* Print all input points */
void
ConvexHull::printPoints(){
    for(auto &i: points){
        cout<<"("<<i->point[0]<<","<<i->point[1]<<","<<i->point[2]<<")"<<endl;
    }
}

/* Initialize convex hull with first 4 points */
void 
ConvexHull::_init(){
    _addFace(points[0], points[1], points[2], points[3]);
    _addFace(points[0], points[1], points[3], points[2]);
    _addFace(points[0], points[2], points[3], points[1]);
    _addFace(points[1], points[2], points[3], points[0]);
    flags[0] = flags[1] = flags[2] = flags[3] = true;
    // TODO: Colinear and coplanar case

}

/* Reset all faces to invisible */
void
ConvexHull::_resetFacesVisibility(){
    for(int i = 0; i < faces.size(); i++){
        faces[i]->visible = false;
    }
}


void
ConvexHull::_addFace(Point3d *p1, Point3d *p2, Point3d *p3, Point3d *inner){   
    /* get edge of point1, point2 */
    Edge *edge12 = getEdge(p1, p2);
    if(edge12 == nullptr){
        /* add edge to point */
        edge12 = new Edge(p1, p2);
        p1->edges.insert(edge12);
        p2->edges.insert(edge12);
    }
    /* get edge of point1, point3 */
    Edge *edge13 = getEdge(p1, p3);
    if(edge13 == nullptr){
        /* add edge to point */
        edge13 = new Edge(p1, p3);
        p1->edges.insert(edge13);
        p3->edges.insert(edge13);
    }
    /* get edge of point2, point3 */
    Edge *edge23 = getEdge(p2, p3);
    if(edge23 == nullptr){
        /* add edge to point */
        edge23 = new Edge(p2, p3);
        p2->edges.insert(edge23);
        p3->edges.insert(edge23);
    }
    /* add edges */
    edges.push_back(edge12);
    edges.push_back(edge13);
    edges.push_back(edge23);

    /* add new face */
    Face *face = new Face(p1, p2, p3);
    if(computeVolumn(face, inner) < 0){
        swap(face->p1, face->p3);
        swap(face->e12, face->e23);
    }
    faces.push_back(face); 
}

/* main function of incremental convex hull */
bool
ConvexHull::run(){
    /* Get the initial convex hull */
    ConvexHull::_init();
    /* Iterate all the rest points */
    for(int i = 0; i < points.size(); i++){
        /* already accessed */
        if(flags[i] == true){
            continue;
        }
        _resetFacesVisibility();
        bool isExterior = false;
        for(int j = 0; j < faces.size(); j++){
            if(computeVolumn(faces[j], points[i]) < 0){
                faces[j]->visible = true;
                isExterior = true;
            }
        }
        /* merge point into convex hull */
        if(isExterior == true){
            /* Find border edge of all visible faces */

            /* construct new face */

            /* remove each visible face */

        }

    }

    return true;
}

#endif
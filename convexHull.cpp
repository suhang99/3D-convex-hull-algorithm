#include "convexHull.hpp"

/* Copy input points */
IncrementalConvexHull::IncrementalConvexHull(vector<Vector3d> pts){
    /* set all input points */
    points.resize(pts.size());
    for(int i = 0; i < pts.size(); i++){
        points[i] = new Point3d(pts[i], i);
    }
    /* set all points unexplored */
    flags.resize(pts.size());
    for(auto i = flags.begin(); i != flags.end(); i++){
        *i = false;
    }
}

IncrementalConvexHull::~IncrementalConvexHull(){
    /* release all points */
    for(auto it = points.begin(); it != points.end(); it++)
        delete *it;
    /* release all edges */
    for(auto it = edges.begin(); it != edges.end(); it++)
        delete *it;
    /* release all faces */
    for(auto it = faces.begin(); it != faces.end(); it++)
        delete *it;
}

/* Print all input points */
void
IncrementalConvexHull::printPoints(){
    for(auto &i: vertice)
        cout<<"("<<i->point[0]<<","<<i->point[1]<<","<<i->point[2]<<")"<<endl;
}

/* Initialize convex hull with first 4 points */
void 
IncrementalConvexHull::_init(){
    inner_point.point = (points[0]->point + points[1]->point + 
                         points[2]->point + points[3]->point) / 4;
    _addFace(points[0], points[1], points[2]);
    _addFace(points[0], points[1], points[3]);
    _addFace(points[0], points[2], points[3]);
    _addFace(points[1], points[2], points[3]);
    flags[0] = flags[1] = flags[2] = flags[3] = true;
    vertice.insert(points[0]);
    vertice.insert(points[1]);
    vertice.insert(points[2]);
    vertice.insert(points[3]);
    // TODO: Colinear and coplanar case

}

Edge*
IncrementalConvexHull::_addEdge(Point3d* p1, Point3d* p2){
    Edge* edge = new Edge(p1, p2);
    p1->edges.insert(edge);
    p2->edges.insert(edge);
    edges.insert(edge);
    return edge;
}

Face*
IncrementalConvexHull::_addFace(Point3d *p1, Point3d *p2, Point3d *p3){   
    Edge *edge12 = getEdge(p1, p2);
    Edge *edge13 = getEdge(p1, p3);
    Edge *edge23 = getEdge(p2, p3);
    if(edge12 == nullptr)
        edge12 = _addEdge(p1, p2);
    if(edge13 == nullptr)
        edge13 = _addEdge(p1, p3);
    if(edge23 == nullptr)
        edge23 = _addEdge(p2, p3);

    /* add new face */
    Face *face = new Face(p1, p2, p3);
    /* add edges to face */
    face->e12 = edge12;
    face->e13 = edge13;
    face->e23 = edge23;

    /* Change the order to make the face pointing outside */
    if(computeVolumn(face, &inner_point) < 0){
        swap(face->p1, face->p3);
        swap(face->e12, face->e23);
    }
    faces.insert(face);

    /* Connect edges to face */
    if(edge12->f1 == nullptr)
        edge12->f1 = face;
    else
        edge12->f2 = face;

    if(edge13->f1 == nullptr)
        edge13->f1 = face;
    else
        edge13->f2 = face;
    
    if(edge23->f1 == nullptr)
        edge23->f1 = face;
    else
        edge23->f2 = face;
    
    return face;
}

void
IncrementalConvexHull::_removeFace(Face *f){
    faces.erase(f);
    delete f;
}

void
IncrementalConvexHull::_removeEdge(Edge *e){
    edges.erase(e);
    e->p1->edges.erase(e);
    e->p2->edges.erase(e);
    delete e;
}

/* main function of incremental convex hull */
bool
IncrementalConvexHull::run(){
    /* Get the initial convex hull */
    _init();
    /* Iterate all the rest points */
    for(int i = 0; i < points.size(); i++){
        /* already explored */
        if(flags[i] == true){
            continue;
        }
        /* Find all visible edges and faces */
        set<Face*> visible_faces;
        set<Edge*> visible_edges;
        set<Point3d*> visible_points;
        for(auto face = faces.begin(); face != faces.end(); face++){
            if(computeVolumn(*face, points[i]) < 0){
                visible_faces.insert(*face);
                visible_edges.insert((*face)->e12);
                visible_edges.insert((*face)->e13);
                visible_edges.insert((*face)->e23);
                visible_points.insert((*face)->p1);
                visible_points.insert((*face)->p2);
                visible_points.insert((*face)->p3);
            }
        }
        /* merge point into convex hull */
        if(!visible_faces.empty()){
            for(auto it = visible_edges.begin(); it != visible_edges.end(); it++){
                Face *new_face = nullptr;
                /* Find border edge */
                if(visible_faces.find((*it)->f1) != visible_faces.end() &&
                   visible_faces.find((*it)->f2) == visible_faces.end()){
                    /* construct new face */
                    (*it)->f1 = nullptr;
                    new_face = _addFace((*it)->p1, (*it)->p2, points[i]);
                    visible_points.erase((*it)->p1);
                    visible_points.erase((*it)->p2);
                }
                else if(visible_faces.find((*it)->f1) == visible_faces.end() &&
                        visible_faces.find((*it)->f2) != visible_faces.end()){
                    (*it)->f2 = nullptr;
                    new_face = _addFace((*it)->p1, (*it)->p2, points[i]);
                    visible_points.erase((*it)->p1);
                    visible_points.erase((*it)->p2);
                }
                else{
                    /* remove edge */
                    _removeEdge(*it);
                }
            }
            /* Remove all visible faces */
            for(auto it = visible_faces.begin(); it != visible_faces.end(); it++){
                _removeFace(*it);
            }
            /* remove hidden points from convex hull */
            for(auto it = visible_points.begin(); it != visible_points.end(); it++){
                vertice.erase(*it);
            }
            /* add new point to convex hull */
            vertice.insert(points[i]);
        }

        /* set this point explored */
        flags[i] = true;
    }
    return true;
}

void
IncrementalConvexHull::plot(string mode){
    using namespace open3d::geometry;
    using namespace open3d::visualization;

    PointCloud pcd;
    TriangleMesh mesh;

    if(mode == "point"){
        /* Plot all input points */
        for(auto i: points)
            pcd.points_.push_back(i->point);

        shared_ptr<PointCloud> pcd_ptr = make_shared<PointCloud>(pcd);
        DrawGeometries({pcd_ptr}, "point");
    }
    else if(mode == "mesh"){
        /* plot the mesh of convex hull */
        for(auto i: points)
            mesh.vertices_.push_back(i->point);
        for(auto i: faces)
            mesh.triangles_.push_back({i->p1->id, i->p2->id, i->p3->id});
        
        shared_ptr<TriangleMesh> mesh_ptr = make_shared<TriangleMesh>(mesh);
        DrawGeometries({mesh_ptr}, "mesh", 640, 480, 50, 50, false, true);
    }
    else if(mode == "convex hull"){
        /* plot both points and mesh */
        for(auto i: points)
            pcd.points_.push_back(i->point);
        for(auto i: points)
            mesh.vertices_.push_back(i->point);
        for(auto i: faces)
            mesh.triangles_.push_back({i->p1->id, i->p2->id, i->p3->id});
        shared_ptr<PointCloud> pcd_ptr = make_shared<PointCloud>(pcd);
        shared_ptr<TriangleMesh> mesh_ptr = make_shared<TriangleMesh>(mesh);
        DrawGeometries({pcd_ptr, mesh_ptr}, "convex hull", 640, 480, 50, 50, false, true);
    }

}

/* detect whether one convex hull collide with another */
bool
IncrementalConvexHull::detectCollision(const IncrementalConvexHull *another){
    bool 
    
    /* Find one face of this which all vertice of another are outside */
    for(auto face: faces){
        for(auto vertex: another->vertice){
            /* Check whether the point is outside the face */
            if(computeVolumn(face, vertex) < 0){

            }
        }
    }

    /* Find faces on the other hull */


}
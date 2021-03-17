#include "convexHull.hpp"

namespace cs271{

/* Copy input points */
ConvexHull::ConvexHull(vector<Vector3d> pts){
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

/* Read from file */
ConvexHull::ConvexHull(const string filename){
    using namespace open3d::io;
    using namespace open3d::geometry;
    using namespace open3d::visualization;

    points.clear();
    if(filename.substr(filename.size()-3, 3) == "txt"){
        ifstream ifs(filename);
        string line;
        stringstream ss;
        int line_cnt = 0;
        while(getline(ifs, line)){
            ss.clear();
            double x, y, z;
            ss<<line;
            ss>>x>>y>>z;
            points.push_back(new Point3d(Vector3d(x,y,z), line_cnt));
            line_cnt++;
        }
        ifs.close();
    }
    else{
        PointCloud pcd;
        ReadPointCloudOption options;
        ReadPointCloud(filename, pcd, options);

        for(int i = 0; i < pcd.points_.size(); i++){
            points.push_back(new Point3d(pcd.points_[i], i));
        }
    }
    
    flags.resize(points.size());
    for(auto i = flags.begin(); i != flags.end(); i++){
        *i = false;
    }

}

ConvexHull::~ConvexHull(){
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
ConvexHull::printPoints(){
    for(auto i: vertices){
        cout<<*i<<endl;
    }
}

/* Print all faces */
void
ConvexHull::printFaces(){
    for(auto f: faces){
        cout<<*(f->p1)<<" "<<*(f->p2)<<" "<<*(f->p3)<<endl;
    }
}

/* Initialize convex hull with first 4 points */
void 
ConvexHull::_init(){
    /* Find 4 non-coplanar points */
    int idx1 = 0, idx2 = -1, idx3 = -1, idx4 = -1;

    /* Find second point (not overlap with point1) */
    for(int i = idx1 + 1; i < points.size(); i++){
        if(points[idx1]->point != points[i]->point){
            idx2 = i;
            break;
        }
    }
    /* Find third point (not colinear) */
    for(int i = idx2 + 1; i < points.size(); i++){
        if(isColinear(points[idx1], points[idx2], points[i]) == false){
            idx3 = i;
            break;
        }
    }
    /* Find fourth point (not overlap, coplanar) */
    for(int i = idx3 + 1; i < points.size(); i++){
        if(isCoplanar(points[idx1], points[idx2], points[idx3], points[i]) == false){
            idx4 = i;
            break;
        }
    }

    if(idx4 == -1){
        cerr<<"Error: Cannot find initial convex hull\n";
    }

    inner_point.point = (points[idx1]->point + points[idx2]->point + 
                         points[idx3]->point + points[idx4]->point) / 4;
    _addFace(points[idx1], points[idx2], points[idx3]);
    _addFace(points[idx1], points[idx2], points[idx4]);
    _addFace(points[idx1], points[idx3], points[idx4]);
    _addFace(points[idx2], points[idx3], points[idx4]);
    flags[idx1] = flags[idx2] = flags[idx3] = flags[idx4] = true;
    vertices.insert(points[idx1]);
    vertices.insert(points[idx2]);
    vertices.insert(points[idx3]);
    vertices.insert(points[idx4]);

}

Edge*
ConvexHull::_addEdge(Point3d* p1, Point3d* p2){
    Edge* edge = new Edge(p1, p2);
    p1->edges.insert(edge);
    p2->edges.insert(edge);
    edges.insert(edge);
    return edge;
}

Face*
ConvexHull::_addFace(Point3d *p1, Point3d *p2, Point3d *p3){   
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
    if(computeVolumn(face, &inner_point) < -1e-15){
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
ConvexHull::_removeFace(Face *f){
    faces.erase(f);
    delete f;
}

void
ConvexHull::_removeEdge(Edge *e){
    /* already removed */
    if(edges.erase(e) == 0){
        return;
    }
    e->p1->edges.erase(e);
    e->p2->edges.erase(e);
    delete e;
}

/* main function of incremental convex hull */
void
ConvexHull::run(){
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
            if(computeVolumn(*face, points[i]) < -1e-15){
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
            for(auto it: visible_edges){
                Face *new_face = nullptr;
                /* Find border edge */
                if(visible_faces.find(it->f1) != visible_faces.end() &&
                   visible_faces.find(it->f2) == visible_faces.end()){
                    /* construct new face */
                    it->f1 = nullptr;
                    new_face = _addFace(it->p1, it->p2, points[i]);
                    visible_points.erase(it->p1);
                    visible_points.erase(it->p2);
                }
                else if(visible_faces.find(it->f1) == visible_faces.end() &&
                        visible_faces.find(it->f2) != visible_faces.end()){
                    it->f2 = nullptr;
                    new_face = _addFace(it->p1, it->p2, points[i]);
                    visible_points.erase(it->p1);
                    visible_points.erase(it->p2);
                }
                else{
                    /* remove edge */
                    _removeEdge(it);
                }
            }
            /* Remove all visible faces */
            for(auto it: visible_faces){
                _removeFace(it);
            }
            /* remove hidden points from convex hull */
            for(auto it: visible_points){
                vertices.erase(it);
            }
            /* add new point to convex hull */
            vertices.insert(points[i]);
        }

        /* set this point explored */
        flags[i] = true;
    }

}


pair<Vector3d, Vector3d>
ConvexHull::getBoundingBox(){
    /* initialize with inner point */
    double x_min = inner_point.point[0], x_max = inner_point.point[0];
    double y_min = inner_point.point[1], y_max = inner_point.point[1];
    double z_min = inner_point.point[2], z_max = inner_point.point[2];

    /* Find bounding box */
    for(auto vertex: vertices){
        x_min = vertex->point[0] < x_min ? vertex->point[0] : x_min;
        x_max = vertex->point[0] > x_max ? vertex->point[0] : x_max;
        y_min = vertex->point[1] < y_min ? vertex->point[1] : y_min;
        y_max = vertex->point[1] > y_max ? vertex->point[1] : y_max;
        z_min = vertex->point[2] < z_min ? vertex->point[2] : z_min;
        z_max = vertex->point[2] > z_max ? vertex->point[2] : z_max;
    }

    return make_pair(Vector3d(x_min, y_min, z_min), Vector3d(x_max, y_max, z_max));
}


/* detect whether one convex hull collide with another */
bool
isCollide(ConvexHull &hull1, ConvexHull &hull2){
    /* Bounding box test */
    auto bbox1 = hull1.getBoundingBox();
    auto bbox2 = hull2.getBoundingBox();

    /* Check whether bounding box overlap */
    if((bbox1.first[0] > bbox2.second[0] || bbox1.second[0] < bbox2.first[0]) &&
       (bbox1.first[1] > bbox2.second[1] || bbox1.second[1] < bbox2.first[1]) &&
       (bbox1.first[2] > bbox2.second[2] || bbox1.second[2] < bbox2.first[2])){
        return false;   
    }

    /* Separating Axis Theorem in 3D */
    double min1 = numeric_limits<double>::max(), min2 = numeric_limits<double>::max();
    double max1 = -numeric_limits<double>::max(), max2 = -numeric_limits<double>::max();
    for(auto face: hull1.faces){
        min1 = numeric_limits<double>::max();
        min2 = numeric_limits<double>::max();
        max1 = -numeric_limits<double>::max();
        max2 = -numeric_limits<double>::max();
        /* Get normal vector */
        Vector3d normal = (face->p1->point - face->p2->point).cross(face->p1->point - face->p3->point);
        /* Project all vertices onto the axis */
        for(auto vertex: hull1.vertices){
            double distance = normal.dot(vertex->point);
            min1 = distance < min1 ? distance : min1;
            max1 = distance > max1 ? distance : max1;
        }
        for(auto vertex: hull2.vertices){
            double distance = normal.dot(vertex->point);
            min2 = distance < min2 ? distance : min2;
            max2 = distance > max2 ? distance : max2;
        }
        /* Whether points overlap */
        if(min1 < min2 && min2 < max1 ||
           min2 < min1 && min1 < max2){
            continue;
        }
        else{
            /* find separating axis */
            return false;
        }
    }
    for(auto face: hull2.faces){
        min1 = numeric_limits<double>::max();
        min2 = numeric_limits<double>::max();
        max1 = -numeric_limits<double>::max();
        max2 = -numeric_limits<double>::max();
        /* Get normal vector */
        Vector3d normal = (face->p1->point - face->p2->point).cross(face->p1->point - face->p3->point);
        /* Project all vertices onto the axis */
        for(auto vertex: hull1.vertices){
            double distance = normal.dot(vertex->point);
            min1 = distance < min1 ? distance : min1;
            max1 = distance > max1 ? distance : max1;
        }
        for(auto vertex: hull2.vertices){
            double distance = normal.dot(vertex->point);
            min2 = distance < min2 ? distance : min2;
            max2 = distance > max2 ? distance : max2;
        }
        /* Whether points overlap */
        if(min1 < min2 && min2 < max1 ||
           min2 < min1 && min1 < max2){
            continue;
        }
        else{
            /* find separating axis */
            return false;
        }
    }
    for(auto edge1: hull1.edges){
        for(auto edge2: hull2.edges){
            min1 = numeric_limits<double>::max();
            min2 = numeric_limits<double>::max();
            max1 = -numeric_limits<double>::max();
            max2 = -numeric_limits<double>::max();
            Vector3d vec1 = edge1->p2->point - edge1->p2->point;
            Vector3d vec2 = edge2->p2->point - edge2->p2->point;
            Vector3d normal = vec1.cross(vec2);
            /* Project all vertices onto the axis */
            for(auto vertex: hull1.vertices){
                double distance = normal.dot(vertex->point);
                min1 = distance < min1 ? distance : min1;
                max1 = distance > max1 ? distance : max1;
            }
            for(auto vertex: hull2.vertices){
                double distance = normal.dot(vertex->point);
                min2 = distance < min2 ? distance : min2;
                max2 = distance > max2 ? distance : max2;
            }
            /* Whether points overlap */
            if(min1 < min2 && min2 < max1 ||
            min2 < min1 && min1 < max2){
                continue;
            }
            else{
                /* find separating axis */
                return false;
            }   
        }
    }

    return true;
}

}
#include "visualizer.hpp"

namespace cs271{

void
Visualizer::plotPoints(ConvexHull &hull){
    PointCloud pcd;
    for(auto point: hull.points){
        pcd.points_.push_back(point->point);
    }
    auto pcd_ptr = make_shared<PointCloud>(pcd);
    DrawGeometries({pcd_ptr}, "Points");
}

void
Visualizer::plotVertex(ConvexHull &hull){
    PointCloud pcd;
    for(auto point: hull.vertices){
        pcd.points_.push_back(point->point);
    }
    auto pcd_ptr = make_shared<PointCloud>(pcd);
    DrawGeometries({pcd_ptr}, "Vertices");
}

void
Visualizer::plotMesh(ConvexHull &hull){
    TriangleMesh mesh;
    for(auto point: hull.points){
        mesh.vertices_.push_back(point->point);
    }
    for(auto face: hull.faces){
        mesh.triangles_.push_back({face->p1->id, face->p2->id, face->p3->id});
    }
    auto mesh_ptr = make_shared<TriangleMesh>(mesh);
    DrawGeometries({mesh_ptr}, "Mesh", 640, 480, 50, 50, false, true);
}

void
Visualizer::plotHull(ConvexHull &hull){
    PointCloud pcd;
    TriangleMesh mesh;
    
    for(auto point: hull.points){
        pcd.points_.push_back(point->point);
        mesh.vertices_.push_back(point->point);
    }
    for(auto face: hull.faces){
        mesh.triangles_.push_back({face->p1->id, face->p2->id, face->p3->id});
    }
    auto pcd_ptr = make_shared<PointCloud>(pcd);
    auto mesh_ptr = make_shared<TriangleMesh>(mesh);
    DrawGeometries({pcd_ptr, mesh_ptr}, "Hull", 640, 480, 50, 50, false, true);
}

void
Visualizer::plotPoints2(ConvexHull &hull1, ConvexHull &hull2){
    PointCloud pcd1, pcd2;
    for(auto point: hull1.points){
        pcd1.points_.push_back(point->point);
    }
    for(auto point: hull2.points){
        pcd2.points_.push_back(point->point);
    }
    auto pcd_ptr1 = make_shared<PointCloud>(pcd1);
    auto pcd_ptr2 = make_shared<PointCloud>(pcd2);
    pcd_ptr1->PaintUniformColor({1, 0, 0});
    pcd_ptr2->PaintUniformColor({0, 0, 1});
    DrawGeometries({pcd_ptr1, pcd_ptr2}, "Points");
}

void
Visualizer::plotVertex2(ConvexHull &hull1, ConvexHull &hull2){
    PointCloud pcd1, pcd2;
    for(auto point: hull1.vertices){
        pcd1.points_.push_back(point->point);
    }
    for(auto point: hull2.vertices){
        pcd2.points_.push_back(point->point);
    }
    auto pcd_ptr1 = make_shared<PointCloud>(pcd1);
    auto pcd_ptr2 = make_shared<PointCloud>(pcd2);
    pcd_ptr1->PaintUniformColor({1, 0, 0});
    pcd_ptr2->PaintUniformColor({0, 0, 1});
    DrawGeometries({pcd_ptr1, pcd_ptr2}, "Vertices");
}

void
Visualizer::plotMesh2(ConvexHull &hull1, ConvexHull &hull2){
    TriangleMesh mesh1, mesh2;
    for(auto point: hull1.points){
        mesh1.vertices_.push_back(point->point);
    }
    for(auto point: hull2.points){
        mesh2.vertices_.push_back(point->point);
    }
    for(auto face: hull1.faces){
        mesh1.triangles_.push_back({face->p1->id, face->p2->id, face->p3->id});
    }
    for(auto face: hull2.faces){
        mesh2.triangles_.push_back({face->p1->id, face->p2->id, face->p3->id});
    }
    auto mesh_ptr1 = make_shared<TriangleMesh>(mesh1);
    auto mesh_ptr2 = make_shared<TriangleMesh>(mesh2);
    mesh_ptr1->PaintUniformColor({1, 0, 0});
    mesh_ptr2->PaintUniformColor({0, 0, 1});
    DrawGeometries({mesh_ptr1, mesh_ptr2}, "Mesh", 640, 480, 50, 50, false, true);
}

void
Visualizer::plotHull2(ConvexHull &hull1, ConvexHull &hull2){
    PointCloud pcd1, pcd2;
    TriangleMesh mesh1, mesh2;
    for(auto point: hull1.points){
        pcd1.points_.push_back(point->point);
        mesh1.vertices_.push_back(point->point);
    }
    for(auto point: hull2.points){
        pcd2.points_.push_back(point->point);
        mesh2.vertices_.push_back(point->point);
    }
    for(auto face: hull1.faces){
        mesh1.triangles_.push_back({face->p1->id, face->p2->id, face->p3->id});
    }
    for(auto face: hull2.faces){
        mesh2.triangles_.push_back({face->p1->id, face->p2->id, face->p3->id});
    }
    auto pcd_ptr1 = make_shared<PointCloud>(pcd1);
    auto pcd_ptr2 = make_shared<PointCloud>(pcd2);
    auto mesh_ptr1 = make_shared<TriangleMesh>(mesh1);
    auto mesh_ptr2 = make_shared<TriangleMesh>(mesh2);
    mesh_ptr1->PaintUniformColor({1, 0, 0});
    mesh_ptr2->PaintUniformColor({0, 0, 1});
    DrawGeometries({pcd_ptr1, mesh_ptr1, pcd_ptr2, mesh_ptr2}, "Hull", 640, 480, 50, 50, false, true);
}

}
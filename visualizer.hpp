#ifndef CS271_HW1_visualizer
#define CS271_HW1_visualizer

#include <iostream>
#include <vector>
#include <open3d/Open3D.h>
#include "convexHull.hpp"


namespace cs271{

using namespace std;
using namespace Eigen;
using namespace open3d::geometry;
using namespace open3d::visualization;

class Visualizer{
    
  public:
    Visualizer() = default;

    void plotPoints(ConvexHull&);
    void plotMesh(ConvexHull&);
    void plotHull(ConvexHull&);
    void plotPoints2(ConvexHull&, ConvexHull&);
    void plotMesh2(ConvexHull&, ConvexHull&);
    void plotHull2(ConvexHull&, ConvexHull&);
    void plotHullWithEditing(ConvexHull&);
};
}

#endif
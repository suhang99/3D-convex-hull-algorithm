#include "convexHull.hpp"
#include "visualizer.hpp"
#include <iostream>

using namespace std;
using namespace Eigen;

int main(int argc, char *argv[]){

    if(argc < 2){
        cerr<<"Please input at least one file path"<<endl;
        return 0;
    }

    cs271::Visualizer visualizer;
    cs271::ConvexHull hull(argv[1]);
    hull.run();

    if(argc == 3){
        if(strcmp(argv[2], "point") == 0){
            visualizer.plotPoints(hull);
        }
        else if(strcmp(argv[2], "mesh") == 0){
            visualizer.plotMesh(hull);
        }
        else if(strcmp(argv[2], "vertex") == 0){
            visualizer.plotVertex(hull);
        }
        else{
            visualizer.plotHull(hull);
        }
    }
    else{
        visualizer.plotHull(hull);
    }

    return 0;
}
#include "convexHull.hpp"
#include "visualizer.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
    if(argc < 2){
        cerr<<"Please input two files"<<endl;
        return 0;
    }

    cs271::Visualizer visualizer;
    cs271::ConvexHull hull1(argv[1]), hull2(argv[2]);
    hull1.run();
    hull2.run();

    if(cs271::isCollide(hull1, hull2)){
        cout<<"Collide!"<<endl;
    }
    else{
        cout<<"Not collide"<<endl;
    }

    if(argc == 4){
        if(strcmp(argv[3], "point") == 0){
            visualizer.plotPoints2(hull1, hull2);
        }
        else if(strcmp(argv[3], "mesh") == 0){
            visualizer.plotMesh2(hull1, hull2);
        }
        else if(strcmp(argv[3], "vertex") == 0){
            visualizer.plotVertex2(hull1, hull2);
        }
        else{
            visualizer.plotHull2(hull1, hull2);
        }
    }
    else{
        visualizer.plotHull2(hull1, hull2);
    }
    

    return 0;
}
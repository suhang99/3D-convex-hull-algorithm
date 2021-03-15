#include "point3d.hpp"
#include "edge.hpp"
#include "face.hpp"

namespace cs271{

Edge::Edge():p1(nullptr),p2(nullptr),f1(nullptr),f2(nullptr){}
Edge::Edge(Point3d *_p1, Point3d *_p2):p1(_p1),p2(_p2),f1(nullptr),f2(nullptr){}

/* Find the edge between p1 and p2 */
Edge*
getEdge(Point3d *p1, Point3d *p2){
    for(auto edge: p1->edges){
        if(edge->p1 == p2 || edge->p2 == p2){
            return edge;
        }
    }
    return nullptr;
}

}
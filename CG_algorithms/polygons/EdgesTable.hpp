/**
 * EdgesTable.hpp
 * Class that represent a edges table (ET) for some polygon. It is used
 * in the Scan Line algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef EdgesTable_hpp
#define EdgesTable_hpp

#include "PolygonEdge.hpp"
#include "Vertex2d.hpp"
#include <map>
#include <list>

using namespace std;

typedef map<int, list<PolygonEdge>> ETMap;

class EdgesTable {
public:
    
    EdgesTable(list<Vertex2d>);
    void initScanLineAlgorithm();
    void removeEntryFromMap(int);
    
private:
    ETMap edgesMap;
    list<Vertex2d> polygonVertices;
};

#endif /* EdgesTable_hpp */

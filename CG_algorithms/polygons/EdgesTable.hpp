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
#include "Polygon.hpp"
#include "../common/Vertex2d.hpp"
#include <map>
#include <list>

typedef std::map<int, std::list<PolygonEdge>> ETMap;

class EdgesTable {
public:
    EdgesTable(std::list<Vertex2d>);
    void removeEntryFromMap(int);
    ETMap edgesMap;
};

#endif /* EdgesTable_hpp */

/**
 * EdgesTable.cpp
 * Class that represent a edges table (ET) for some polygon. It is used
 * in the Scan Line algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "EdgesTable.hpp"
#include "Vertex2d.hpp"
#include "PolygonEdge.hpp"
#include <list>

using namespace std;

EdgesTable::EdgesTable(list<Vertex2d> verticesList) {
    
    list<Vertex2d>::const_iterator it;
    int maxY, xForMinY, minY;
    float slope, currentX;
    list<PolygonEdge> listOfEdges;
    
    // TODO: find another way to initialize the map, cause this way just works for the cases
    // when the order of the coordinates is correct
    for (it = verticesList.begin(); it != verticesList.end(); it++) {
        list<Vertex2d>::const_iterator nextCoordinate;
        
        // On last element of the list, we create a edge with the first one,
        // closing the circle
        if (next(it) == verticesList.end()) {
            nextCoordinate = verticesList.begin();
        } else {
            nextCoordinate = next(it);
        }
        
        // if there's no variation in the y axis, we do not include the edge in the table.
        // The algorithm will take care of x xis parallel lines
        if (nextCoordinate->getY() == it->getY()) {
            continue;
        }
        
        // Calculate the inverse of the slope (1/m)m considering zero division
        slope = (nextCoordinate->getX() - it->getX()) / (nextCoordinate->getY() - it->getY());
        
        // Set all needed options to create a edge
        if (nextCoordinate->getY() > it->getY()) {
            maxY = nextCoordinate->getY();
            xForMinY = it->getX();
            currentX = it->getX();
            minY = it->getY();
        } else {
            maxY = it->getY();
            xForMinY = nextCoordinate->getX();
            currentX = nextCoordinate->getX();
            minY = nextCoordinate->getY();
        }
        
        // Create the edge
        PolygonEdge newEdge(minY, currentX, xForMinY, maxY, slope);
        
        // Insert into the map
        ETMap::const_iterator mapIt = edgesMap.find(minY);
        
        // if the specified key has not been found, it returns the end iterator
        if (mapIt == edgesMap.end()) {
            // Insert edge into a list
            listOfEdges.clear();
            listOfEdges.push_back(newEdge);
            
            // Insert list into the map
            edgesMap.insert(pair<int, list<PolygonEdge>>(minY, listOfEdges));
        } else {
            // Just insert it into the list
            edgesMap[minY].push_back(newEdge);
        }
    }
    
}

bool EdgesTable::isEmpty() const {
    return this->edgesMap.empty();
}

ETMap& EdgesTable::getEdgesMap() {
    return this->edgesMap;
}

void EdgesTable::removeEntryFromMap(int keyToRemove) {
    this->edgesMap.erase(keyToRemove);
}

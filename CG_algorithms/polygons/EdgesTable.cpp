/**
 * EdgesTable.cpp
 * Class that represent a edges table (ET) for some polygon. It is used
 * in the Scan Line algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "EdgesTable.hpp"
#include "../common/Vertex2d.hpp"
#include "PolygonEdge.hpp"
#include "Polygon.hpp"
#include <list>
#include <math.h>
#include "OpenGL/gl.h"

using namespace std;

/**
 * Constructor for EdgesTable class.
 * Initializes the map of edges according to the list of vertices passed as parameter.
 * It assumes the list of coordinates is passed in the right order.
 * @param verticesList {list<Vertex2d>} - the list of polygon vertices to draw
 * @return {void}
 */
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
        // The algorithm will take care of lines paralel to the x axis
        if (nextCoordinate->getY() == it->getY()) {
            continue;
        }
        
        // Calculate the inverse of the slope (1/m)
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
        
        // Look for the key corresponding to the current y value
        ETMap::const_iterator mapIt = edgesMap.find(minY);
        
        // if the specified key has not been found, we create a new entry in the map,
        // otherwise, we just insert the new edge into the list referenced by the found key
        if (mapIt == edgesMap.end()) {
            listOfEdges.clear();
            listOfEdges.push_back(newEdge);
            edgesMap.insert(pair<int, list<PolygonEdge>>(minY, listOfEdges));
        } else {
            edgesMap[minY].push_back(newEdge);
        }
    }
    
}

/**
 * Function that removes a key of the ET map.
 * @param keyToRemove {int} - the key to remove from the map
 * @return {void}
 */
void EdgesTable::removeEntryFromMap(int keyToRemove) {
    this->edgesMap.erase(keyToRemove);
}

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
#include <math.h>
#include "OpenGL/gl.h"

using namespace std;

EdgesTable::EdgesTable(list<Vertex2d> verticesList) {
    this->polygonVertices = verticesList;
    
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

void EdgesTable::initScanLineAlgorithm() {
    list<PolygonEdge> activeEdges;
    
    // Get the smaller y from the list of coordinates
    int scanLineY = min_element(this->polygonVertices.begin(), this->polygonVertices.end())->getY();
    
    // Move the list of key scanLineY to active edges and remove it from the edges table
    list<PolygonEdge> initialActiveEdges = this->edgesMap.at(scanLineY);
    activeEdges.merge(initialActiveEdges);
    this->removeEntryFromMap(scanLineY);
    
    // Make sure it is sorted already
    activeEdges.sort();
    
    while (!activeEdges.empty() || !this->isEmpty()) {
        
        // Draw the points
        glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 1.0);
        
        for (auto it = activeEdges.begin(); it != activeEdges.end(); it++) {
            // Get the next edge
            auto nextPolygon = next(it);
            
            // Get the extremes x coordinates
            int leftXValue = ceilf(it->getCurrentX());
            int rightXValue = floorf(nextPolygon->getCurrentX());
            
            // Plot all the points between the two extremes
            for (; leftXValue <= rightXValue; leftXValue++) {
                glVertex3i(leftXValue, scanLineY, 0);
            }
            
            // Make sure it goes on groups of two
            it++;
        }
        
        glEnd();
        
        // Increment the scan line y coordinate
        scanLineY++;
        
        // Remove the edges from the list that had been reached its maximmum y
        activeEdges.remove_if([scanLineY](const PolygonEdge edge){
            return edge.getMaxYCoordinate() == scanLineY;
        });
        
        for (auto it = activeEdges.begin(); it != activeEdges.end(); it++) {
            it->updateCurrentX();
        }
        
        // Make sure the list is sorted after the updates
        activeEdges.sort();
        
        // Move the list of key scanLineY to active edges and remove it from the edges table
        auto foundIt = this->edgesMap.find(scanLineY);
        
        if (foundIt != this->edgesMap.end()) {
            activeEdges.merge(foundIt->second);
            activeEdges.sort();
            this->removeEntryFromMap(scanLineY);
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

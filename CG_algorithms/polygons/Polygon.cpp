/**
 * Polygon.cpp
 * Class to represent a polygon.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "Polygon.hpp"
#include "../common/Vertex2d.hpp"
#include "../2D_transformations/TransformationMatrix.hpp"
#include "../2D_transformations/Matrix2d.hpp"
#include "PolygonEdge.hpp"
#include "EdgesTable.hpp"
#include <list>

using namespace std;

/**
 * Constructor of the class
 * @param listOfVertices {list<Vertex2d>}
 */
Polygon::Polygon(list<Vertex2d> listOfVertices):GeometricFigure() {
    this->setVerticesList(listOfVertices);
}

/**
 * Getter for the vertices
 * @return {list<Vertex2d>}
 */
list<Vertex2d> Polygon::getVerticesList() const {
    return this->vertices;
}

/**
 * Setter for the vertices
 * @param newListOfVertices {list<Vertex2d>}
 */
void Polygon::setVerticesList(list<Vertex2d> newListOfVertices) {
    this->vertices = newListOfVertices;
}

/**
 * Generates a polygon using the Scan Line algorithm
 * @param vertices {list<Vertex2d>}
 */
Polygon Polygon::generatePolygon(list<Vertex2d> vertices) {
    EdgesTable edgesTable(vertices);
    list<PolygonEdge> activeEdges;
    Polygon polygon(vertices);
    Vertex2d pointToAdd;
    
    // Get the smaller y from the list of polygon vertices
    int scanLineY = min_element(vertices.begin(), vertices.end())->getY();
    
    // Move the list of key scanLineY to active edges and remove it from the edges table
    list<PolygonEdge> initialActiveEdges = edgesTable.edgesMap.at(scanLineY);
    activeEdges.merge(initialActiveEdges);
    edgesTable.removeEntryFromMap(scanLineY);
    
    // Make sure it is sorted already
    activeEdges.sort();
    
    while (!activeEdges.empty() || !edgesTable.edgesMap.empty()) {
        for (auto it = activeEdges.begin(); it != activeEdges.end(); it++) {
            // Get the next edge
            auto nextPolygon = next(it);
            
            // Get the extremes x coordinates
            int leftXValue = ceilf(it->getCurrentX());
            int rightXValue = floorf(nextPolygon->getCurrentX());
            
            // Add all the points between the two extremes to the polygon
            for (; leftXValue <= rightXValue; leftXValue++) {
                pointToAdd.setX(leftXValue);
                pointToAdd.setY(scanLineY);
                polygon.addPoint(pointToAdd);
            }
            
            // Make sure it goes on groups of two
            it++;
        }
        
        // Increment the scan line y coordinate
        scanLineY++;
        
        // Remove the edges from the list that had been reached its maximmum y
        activeEdges.remove_if([scanLineY](const PolygonEdge edge){
            return edge.getMaxYCoordinate() == scanLineY;
        });
        
        // Update the currentX values of the polygons in the active edges list
        for (auto it = activeEdges.begin(); it != activeEdges.end(); it++) {
            it->updateCurrentX();
        }
        
        // Make sure the list is sorted after the updates
        activeEdges.sort();
        
        // Look for an entry for the current y value
        auto foundIt = edgesTable.edgesMap.find(scanLineY);
        
        // If we find, we move the found list from the edges table to the active edges list
        if (foundIt != edgesTable.edgesMap.end()) {
            activeEdges.merge(foundIt->second);
            activeEdges.sort();
            edgesTable.removeEntryFromMap(scanLineY);
        }
    }
    
    return polygon;
}

void Polygon::applyTransformationMatrix(Matrix2d transformationMatrix) {
    list<Vertex2d> newVerticeList;
    Vertex2d newVertice;
    
    // Generate the new vertices list
    for (Vertex2d vertice : this->getVerticesList()) {
        newVertice = transformationMatrix * vertice;
        newVerticeList.push_back(newVertice);
    }
    
    // Create a new polygon with the new vertices
    Polygon newPolygon = Polygon::generatePolygon(newVerticeList);
    
    // Set the new properties
    this->setVerticesList(newVerticeList);
    GeometricFigure::setPoints(newPolygon.GeometricFigure::getPoints());
}

void Polygon::translate(float dx, float dy) {
    Matrix2d translationMatrix = TransformationMatrix::getInstance()->getTranslationMatrix(dx, dy);
    this->applyTransformationMatrix(translationMatrix);
}

void Polygon::scale(float xFactor, float yFactor, float xPivot, float yPivot) {
    Matrix2d scaleMatrix = TransformationMatrix::getInstance()->getScaleMatrix(xFactor, yFactor, xPivot, yPivot);
    this->applyTransformationMatrix(scaleMatrix);
}

void Polygon::rotate(float angle, float xPivot, float yPivot) {
    Matrix2d rotationMatrix = TransformationMatrix::getInstance()->getRotationMatrix(angle, xPivot, yPivot);
    this->applyTransformationMatrix(rotationMatrix);
}
/**
 * Polygon.cpp
 * Class to represent a polygon.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "Polygon.hpp"
#include "../common/Vertex2d.hpp"
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
    return this->getVerticesList();
}

/**
 * Setter for the vertices
 * @param newListOfVertices {list<Vertex2d>}
 */
void Polygon::setVerticesList(list<Vertex2d> newListOfVertices) {
    this->vertices = newListOfVertices;
}

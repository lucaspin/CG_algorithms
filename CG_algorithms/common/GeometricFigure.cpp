/**
 * GeometricFigure.cpp
 * Class to represent a geometric figure..
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "GeometricFigure.hpp"
#include "../common/Vertex2d.hpp"
#include "OpenGL/gl.h"

using namespace std;

/**
 * Gets the points that forms the geometric figure
 * @return points {vector<int>}
 */
vector<Vertex2d> GeometricFigure::getPoints() const {
    return this->points;
}

/**
 * Sets the points that will form the geometric figure
 * @param newPoints {vector<int>} the new figure points
 */
void GeometricFigure::setPoints(vector<Vertex2d> newPoints) {
    this->points = newPoints;
}

/**
 * Add a new point to the geometric figure
 * @param newPoint {Vertex2d}
 */
void GeometricFigure::addPoint(Vertex2d newPoint) {
    this->points.push_back(newPoint);
}

/**
 * Plot the geometric figure points in the screen,
 * using OpenGL library
 */
void GeometricFigure::plotPoints() {
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    
    for (Vertex2d point : this->getPoints()) {
        glVertex3i(point.getX(), point.getY(), point.getZ() - 1);
    }
    
    glEnd();
}

/**
 * Set the type of the GeometricFigure
 * @param _type {GeometricFigureType}
 */
void GeometricFigure::setType(GeometricFigureType _type) {
    this->type = _type;
}

/**
 * Get the type of the GeometricFigure
 * @return type {GeometricFigureType}
 */
GeometricFigureType GeometricFigure::getType() {
    return this->type;
}

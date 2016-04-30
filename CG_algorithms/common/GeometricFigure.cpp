/**
 * GeometricFigure.cpp
 * Class to represent a geometric figure..
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "GeometricFigure.hpp"
#include "../common/Vertex2d.hpp"

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

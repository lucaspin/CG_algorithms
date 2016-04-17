/**
 * PolygonEdge.cpp
 * Class that represent a edge of a polygon to be formed. It is used
 * in the Scan Line algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "PolygonEdge.hpp"

/**
 * Constructor for the class
 * @param minYCoordinate {int} - the minimmum y value of the edge
 * @param currentX {int} - the current x value for some iteration
 * @param xForMinY {int} - the x value for the minimmum y coordinate of the edge
 * @param maxYCoordinate {int} - the maximmum y value of the edge
 * @param slope {float} - the variation used to increment he current x of the edge (1/m)
 */
PolygonEdge::PolygonEdge(int minYCoordinate, int currentX, int xForMinY, int maxYCoordinate, float slope) {
    this->setCurrentX(currentX);
    this->setMaxYCoordinate(maxYCoordinate);
    this->setMinYCoordinate(minYCoordinate);
    this->setSlope(slope);
    this->setXForMinY(xForMinY);
}

/**
 * Overload handler for the less than operator
 */
bool PolygonEdge::operator<(const PolygonEdge& _polygonEdge) const {
    return this->currentX < _polygonEdge.getCurrentX();
}

/**
 * Function to update the currentX value. Called on every Scan Line algorithm iteration
 * @return {void}
 */
void PolygonEdge::updateCurrentX() {
    this->currentX += this->slope;
}

/**
 * Getter for the currentX value
 * @return currentX {float}
 */
float PolygonEdge::getCurrentX() const {
    return this->currentX;
}

/**
 * Getter for the minimmum y coordinate
 * @return {int} the minimmum y coordinate of the edge
 */
int PolygonEdge::getMinYCoordinate() const {
    return this->minYCoordinate;
}

/**
 * Getter for the maximmum y coordinate
 * @return maxYCoordinate {int} - the maximmum y coordinate of the edge
 */
int PolygonEdge::getMaxYCoordinate() const {
    return this->maxYCoordinate;
}

/**
 * Getter for the x value of the minimmum y coordinate
 * @return xForMinY {int}
 */
int PolygonEdge::getXForMinY() const {
    return this->xForMinY;
}

/**
 * Getter for the slope
 * @return slope {float}
 */
float PolygonEdge::getSlope() const {
    return this->slope;
}

/**
 * Setter for the slope
 * @param newSlope {float}
 */
void PolygonEdge::setSlope(float newSlope) {
    this->slope = newSlope;
}

/**
 * Setter for the current x value
 * @param newCurrentX {float}
 */
void PolygonEdge::setCurrentX(float newCurrentX) {
    this->currentX = newCurrentX;
}

/**
 * Setter for minimmum y coordinate
 * @param minYCoordinate {int}
 */
void PolygonEdge::setMinYCoordinate(int minYCoordinate) {
    this->minYCoordinate = minYCoordinate;
}

/**
 * Setter for the maximmum y coordinate
 * @param yCoordinate {int}
 */
void PolygonEdge::setMaxYCoordinate(int yCoordinate) {
    this->maxYCoordinate = yCoordinate;
}

/**
 * Setter for the minimmum y coordinate
 * @param xForMinY {int}
 */
void PolygonEdge::setXForMinY(int xForMinY) {
    this->xForMinY = xForMinY;
}
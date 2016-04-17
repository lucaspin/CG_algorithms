/**
 * PolygonEdge.cpp
 * Class that represent a edge of a polygon to be formed. It is used
 * in the Scan Line algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "PolygonEdge.hpp"

PolygonEdge::PolygonEdge(int minYCoordinate, int currentX, int xForMinY, int maxYCoordinate, float slope) {
    this->setCurrentX(currentX);
    this->setMaxYCoordinate(maxYCoordinate);
    this->setMinYCoordinate(minYCoordinate);
    this->setSlope(slope);
    this->setXForMinY(xForMinY);
}

bool PolygonEdge::operator<(const PolygonEdge& _polygonEdge) const {
    return this->currentX < _polygonEdge.getCurrentX();
}

void PolygonEdge::updateCurrentX() {
    this->currentX += this->slope;
}

float PolygonEdge::getCurrentX() const {
    return this->currentX;
}

int PolygonEdge::getMinYCoordinate() const {
    return this->minYCoordinate;
}

int PolygonEdge::getMaxYCoordinate() const {
    return this->maxYCoordinate;
}

int PolygonEdge::getXForMinY() const {
    return this->xForMinY;
}

float PolygonEdge::getSlope() const {
    return this->slope;
}

void PolygonEdge::setSlope(float newSlope) {
    this->slope = newSlope;
}

void PolygonEdge::setCurrentX(float newCurrentX) {
    this->currentX = newCurrentX;
}

void PolygonEdge::setMinYCoordinate(int minYCoordinate) {
    this->minYCoordinate = minYCoordinate;
}

void PolygonEdge::setMaxYCoordinate(int yCoordinate) {
    this->maxYCoordinate = yCoordinate;
}

void PolygonEdge::setXForMinY(int xForMinY) {
    this->xForMinY = xForMinY;
}
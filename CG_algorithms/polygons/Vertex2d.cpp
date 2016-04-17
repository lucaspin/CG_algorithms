/**
 * Vertex2d.cpp
 * Class that represent a coordinate in two dimensions. It is used
 * in the Scan Line algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "Vertex2d.hpp"

Vertex2d::Vertex2d(float x, float y) {
    this->setX(x);
    this->setY(y);
}

bool Vertex2d::operator<(const Vertex2d& point) const {
    return this->y < point.getY();
}

float Vertex2d::getX() const {
    return this->x;
}

float Vertex2d::getY() const {
    return this->y;
}

void Vertex2d::setX(float _x) {
    this->x = _x;
}

void Vertex2d::setY(float _y) {
    this->y = _y;
}
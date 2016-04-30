/**
 * Vertex2d.cpp
 * Class that represent a coordinate in two dimensions. It is used
 * in the Scan Line algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "Vertex2d.hpp"

/**
 * Constructor that initialize all the coordinates to 0
 */
Vertex2d::Vertex2d() {
    this->setX(0.0f);
    this->setY(0.0f);
    this->setZ(1.0f);
}

/**
 * @constructor
 * @param {float} - the x coordinate of the point
 * @param {float} - the y coordinate of the point
 */
Vertex2d::Vertex2d(float x, float y, float z) {
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

/**
 * Overload handler for the less than operator
 */
bool Vertex2d::operator<(const Vertex2d& point) const {
    return this->y < point.getY();
}

/**
 * Getter for the x coordinate
 * @return {float}
 */
float Vertex2d::getX() const {
    return this->x;
}

/**
 * Getter for the y coordinate
 * @return {float}
 */
float Vertex2d::getY() const {
    return this->y;
}

/**
 * Gets the z value of the vertex
 * @return {float}
 */
float Vertex2d::getZ() const {
    return this->z;
}

/**
 * Setter for the x coordinate
 * @param _x {float} - the new x coordinate
 */
void Vertex2d::setX(float _x) {
    this->x = _x;
}

/**
 * Setter for the y coordinate
 * @param _y {float} - the new y coordinate
 */
void Vertex2d::setY(float _y) {
    this->y = _y;
}

/**
 * Setter for the z coordinate
 * @param _z {float} - the new z coordinate
 */
void Vertex2d::setZ(float _z) {
    this->z = _z;
}

/**
 * Returns the length of this vector (Read Only)
 * @return {float}
 */
float Vertex2d::magnitude() const {
    float _magnitude = sqrt(x*x + y*y);
    return _magnitude;
}
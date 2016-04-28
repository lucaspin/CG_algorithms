/**
 * Vertex2d.cpp
 * Class that represent a coordinate in two dimensions. It is used
 * in the Scan Line algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "Vertex2d.hpp"


/**
 * @constructor
 */
Vertex2d::Vertex2d() {
    vector<float> initialValues = {0,0,1};
    this->vertex = initialValues;
}

/**
 * @constructor
 * @param {float} - the x coordinate of the point
 * @param {float} - the y coordinate of the point
 */
Vertex2d::Vertex2d(float x, float y) {
    vector<float> initialValues = {x,y,1};
    this->vertex = initialValues;
}

/**
 * @ Setter for the entire vector
 * @param {vector<float>}
 */
void Vertex2d::setVertex2d( vector<float> initialValues ) {
    this->vertex = initialValues;
}


/**
 * Overload handler for the less than operator
 */
bool Vertex2d::operator<(const Vertex2d& point) const {
    return this->vertex[1] < point.getY();
}

/**
 * Getter for the x coordinate
 */
float Vertex2d::getX() const {
    return this->vertex[0];
}

/**
 * Getter for the y coordinate
 */
float Vertex2d::getY() const {
    return this->vertex[1];
}

/**
 * Setter for the x coordinate
 * @param _x {float} - the new x coordinate
 */
void Vertex2d::setX(float _x) {
    this->vertex[0] = _x;
}

/**
 * Setter for the y coordinate
 * @param _y {float} - the new y coordinate
 */
void Vertex2d::setY(float _y) {
    this->vertex[1] = _y;
}

/**
 * Returns the length of this vector (Read Only)
 */
float Vertex2d::magnitude() const{
    float x = this->getX();
    float y = this->getY();
    float _magnitude = sqrt(x*x + y*y);
    return _magnitude;
}


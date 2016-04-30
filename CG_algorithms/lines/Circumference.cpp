/**
 * Circumference.cpp
 * Class to represent a circumference.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "Circumference.hpp"
#include <vector>
#include "../common/Vertex2d.hpp"

using namespace std;

/**
 * Constructor for the class
 */
Circumference::Circumference(int radius):GeometricFigure() {
    this->setRadius(radius);
}

/**
 * Setter for the circumference's radius
 * @param radius {int}
 */
void Circumference::setRadius(int newRadius) {
    if (radius < 0) {
        throw invalid_argument("A circumference must have a positive radius");
    }
    
    this->radius = newRadius;
}

/**
 * Getter for the circumference's radius
 * @return {int} - the radius of the circunference
 */
int Circumference::getRadius() const {
    return this->radius;
}

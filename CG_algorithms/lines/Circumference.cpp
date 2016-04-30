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
 * Generate the points for a circunference
 * @param circumference (Circumference*)
 * @param center {Vertex2d} - the center of the circumference
 * @param currentPoint {Vertex2d} - the current point
 */
 void Circumference::generateCircumferencePoints(Circumference *circumference, Vertex2d center, Vertex2d currentPoint) {
    Vertex2d pointToAdd;
    int x = currentPoint.getX();
    int y = currentPoint.getY();
    
    pointToAdd.setX(center.getX() + x);
    pointToAdd.setY(center.getY() + y);
    circumference->addPoint(pointToAdd);
    
    pointToAdd.setX(center.getX() + y);
    pointToAdd.setY(center.getY() + x);
    circumference->addPoint(pointToAdd);
    
    pointToAdd.setX(center.getX() + y);
    pointToAdd.setY(center.getY() - x);
    circumference->addPoint(pointToAdd);
    
    pointToAdd.setX(center.getX() + x);
    pointToAdd.setY(center.getY() - y);
    circumference->addPoint(pointToAdd);
    
    pointToAdd.setX(center.getX() - x);
    pointToAdd.setY(center.getY() - y);
    circumference->addPoint(pointToAdd);
    
    pointToAdd.setX(center.getX() - y);
    pointToAdd.setY(center.getY() - x);
    circumference->addPoint(pointToAdd);
    
    pointToAdd.setX(center.getX() - y);
    pointToAdd.setY(center.getY() + x);
    circumference->addPoint(pointToAdd);
    
    pointToAdd.setX(center.getX() - x);
    pointToAdd.setY(center.getY() + y);
    circumference->addPoint(pointToAdd);
}

/**
 * Generate a circumference, using the Bresenham algorithm for circumferences
 * @param center {Vertex2d} the coordinate of the circumference's center
 * @param radius the radius of the circumference
 */
Circumference Circumference::generateCircumferenceBresenham(Vertex2d center, int radius) {
    int currentX, currentY, d;
    Circumference circumference(radius);
    Circumference *reference = &circumference;
    Vertex2d currentPoint;
    
    currentPoint.setX(0);
    currentPoint.setY(radius);
    d = 1 - radius;
    
    Circumference::generateCircumferencePoints(reference, center, currentPoint);
    
    currentX = currentPoint.getX();
    currentY = currentPoint.getY();
    
    while (currentX < currentY) {
        currentX = currentPoint.getX();
        currentY = currentPoint.getY();
        
        if (d < 0) {
            d = d + (2 * currentX) + 3;
        } else {
            d = d + 2 * (currentX - currentY) + 5;
            currentPoint.setY(currentY - 1);
        }
        
        currentPoint.setX(currentX + 1);
        generateCircumferencePoints(reference, center, currentPoint);
    }
    
    return circumference;
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

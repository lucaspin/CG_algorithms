/**
 * Circumference.cpp
 * Class to represent a circumference.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "Circumference.hpp"
#include <vector>
#include "../2D_transformations/Matrix2d.hpp"
#include "../2D_transformations/TransformationMatrix.hpp"
#include "../common/Vertex2d.hpp"

using namespace std;

/**
 * Constructor for the class
 * @param center {Vertex2d}
 * @param radius {int}
 */
Circumference::Circumference(Vertex2d center, int radius):GeometricFigure() {
    this->setCenter(center);
    this->setRadius(radius);
    GeometricFigure::setType(CIRCUMFERENCE);
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
    Circumference circumference(center, radius);
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
    if (newRadius < 0) {
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

/**
 * Getter for the circumference's center
 * @return {Vertex2d}
 */
Vertex2d Circumference::getCenter() const {
    return this->center;
}

/**
 * Setter for the circumference's center
 * @param newCenter {Vertex2d}
 */
void Circumference::setCenter(Vertex2d newCenter) {
    this->center = newCenter;
}

void Circumference::applyTransformationMatrix(Matrix2d transformationMatrix) {
    // Generate a new center
    Vertex2d newCenter = transformationMatrix * this->getCenter();
    
    // Generate a new circumference with the new center
    Circumference newCirc = Circumference::generateCircumferenceBresenham(newCenter, this->getRadius());
    
    // Set the new points
    this->setCenter(newCenter);
    GeometricFigure::setPoints(newCirc.GeometricFigure::getPoints());
}

void Circumference::translate(float dx, float dy) {
    Matrix2d translationMatrix = TransformationMatrix::getInstance()->getTranslationMatrix(dx, dy);
    this->applyTransformationMatrix(translationMatrix);
}

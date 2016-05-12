/**
 * Line.cpp
 * Class to represent a line.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "Line.hpp"
#include <vector>
#include <cmath>
#include "../common/Vertex2d.hpp"
#include "../2D_transformations/TransformationMatrix.hpp"
#include "../2D_transformations/Matrix2d.hpp"

using namespace std;

/**
 * Constructor for the class
 * @param initialPoint {Vertex2d}
 * @param finalPoint {Vertex2d}
 */
Line::Line(Vertex2d initialPoint, Vertex2d finalPoint):GeometricFigure() {
    this->setInitialPoint(initialPoint);
    this->setFinalPoint(finalPoint);
    GeometricFigure::setType(LINE);
}

/**
 * Constructor for the class
 * @param x1 {float}
 * @param y1 {float}
 * @param x2 {float}
 * @param y2 {float}
 */
Line::Line(float x1, float y1, float x2, float y2):GeometricFigure() {
    Vertex2d initialPoint(x1, y1);
    Vertex2d finalPoint(x2, y2);
    this->setInitialPoint(initialPoint);
    this->setFinalPoint(finalPoint);
    GeometricFigure::setType(LINE);
}

/**
 * Generate a line, using the Bresenham algorithm
 * @param initialPoint {Vertex2d} - the initial coordinate of the line
 * @param lastPoint {Vertex2d} - the last coordinate of the line
 */
Line Line::generateLineBresenham(Vertex2d initialPoint, Vertex2d lastPoint) {
    int xVariation, yVariation, currentX, currentY;
    int const1, const2, d, lastX;
    Line line(initialPoint, lastPoint);
    Vertex2d pointToAdd;
    
    xVariation = abs((lastPoint.getX() - initialPoint.getX()));
    yVariation = abs((lastPoint.getY() - initialPoint.getY()));
    
    d = (2 * xVariation) - yVariation;
    const1 = 2 * xVariation;
    const2 = 2 * (yVariation - xVariation);
    
    if (initialPoint.getX() > lastPoint.getX()) {
        currentX = lastPoint.getX();
        currentY = lastPoint.getY();
        lastX = initialPoint.getX();
    } else {
        currentX = initialPoint.getX();
        currentY = initialPoint.getY();
        lastX = lastPoint.getX();
    }
    
    pointToAdd.setX(currentX);
    pointToAdd.setY(currentY);
    line.addPoint(pointToAdd);
    
    while (currentX < lastX) {
        currentX++;
        if (d < 0) {
            d += const1;
        } else {
            currentY++;
            d += const2;
        }
        pointToAdd.setX(currentX);
        pointToAdd.setY(currentY);
        line.addPoint(pointToAdd);
    }
    
    return line;
}

/**
 * Display a line on the screen, using the DDA algorithm
 * @param initialPoint - the initial coordinate of the line
 * @param lastPoint - the last coordinate of the line
 */
Line Line::generateLineDDA(Vertex2d initialPoint, Vertex2d lastPoint) {
    int xVariation, yVariation;
    float xIncrement, yIncrement;
    int numOfIterations, count;
    float currentX, currentY;
    
    Line line(initialPoint, lastPoint);
    Vertex2d pointToAdd;
    
    xVariation = lastPoint.getX() - initialPoint.getX();
    yVariation = lastPoint.getY() - initialPoint.getY();
    
    if (abs(xVariation) > abs(yVariation)) {
        numOfIterations = abs(xVariation);
    } else {
        numOfIterations = abs(yVariation);
    }
    
    xIncrement = (float) xVariation / numOfIterations;
    yIncrement = (float) yVariation / numOfIterations;
    
    currentX = initialPoint.getX();
    currentY = initialPoint.getY();
    
    pointToAdd.setX(round(currentX));
    pointToAdd.setY(round(currentY));
    line.addPoint(pointToAdd);
    
    for (count = 1; count < numOfIterations; count++) {
        currentX += xIncrement;
        currentY += yIncrement;
        
        pointToAdd.setX(round(currentX));
        pointToAdd.setY(round(currentY));
        line.addPoint(pointToAdd);
    }
    
    return line;
}

/**
 * Getter for the initial point of the line
 * @return {Vertex2d}
 */
Vertex2d Line::getInitialPoint() const {
    return this->initialPoint;
}

/**
 * Getter for the final point of the line
 * @return {Vertex2d}
 */
Vertex2d Line::getFinalPoint() const {
    return this->finalPoint;
}

/**
 * Setter for the final point of the line
 * @param newFinalPoint {Vertex2d}
 */
void Line::setFinalPoint(Vertex2d newFinalPoint) {
    this->finalPoint = newFinalPoint;
}

/**
 * Setter for the initial point of the line
 * @param newInitialPoint {Vertex2d}
 */
void Line::setInitialPoint(Vertex2d newInitialPoint) {
    this->initialPoint = newInitialPoint;
}

void Line::applyTransformationMatrix(Matrix2d transformationMatrix) {
    // Cslculate the new points
    Vertex2d newInitialPoint = transformationMatrix * this->getInitialPoint();
    Vertex2d newFinalPoint = transformationMatrix * this->getFinalPoint();
    
    // Generate a new line
    Line newLine = generateLineBresenham(newInitialPoint, newFinalPoint);
    
    // Set the new points
    this->setInitialPoint(newInitialPoint);
    this->setFinalPoint(newFinalPoint);
    GeometricFigure::setPoints(newLine.GeometricFigure::getPoints());
}

void Line::translate(float dx, float dy) {
    Matrix2d translationMatrix = TransformationMatrix::getInstance()->getTranslationMatrix(dx, dy);
    this->applyTransformationMatrix(translationMatrix);
}

void Line::scale(float xScaleFactor, float yScaleFactor, float xPivot, float yPivot) {
    Matrix2d scaleMatrix = TransformationMatrix::getInstance()->getScaleMatrix(xScaleFactor,
                                                                               yScaleFactor,
                                                                               xPivot, yPivot);
    
    this->applyTransformationMatrix(scaleMatrix);
}

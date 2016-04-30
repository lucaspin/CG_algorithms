/**
 * bresenham.h
 *
 * Library that contains bresenham algorithms for drawing lines and circumferences
 * @author Lucas Pinheiro
 */

#ifndef bresenham_h
#define bresenham_h

#include "../common/Vertex2d.hpp"
#include "Line.hpp"
#include "Circumference.hpp"

Line generateLineBresenham(Vertex2d initialPoint, Vertex2d lastPoint);
Circumference generateCircumferenceBresenham(Vertex2d center, int radius);
void generateCircumferencePoints(Circumference *circumference, Vertex2d center, Vertex2d currentPoint);

/**
 * Generate a line, using the Bresenham algorithm
 * @param initialPoint {Vertex2d} - the initial coordinate of the line
 * @param lastPoint {Vertex2d} - the last coordinate of the line
 */
Line generateLineBresenham(Vertex2d initialPoint, Vertex2d lastPoint) {
    int xVariation, yVariation, currentX, currentY;
    int const1, const2, d, lastX;
    Line line;
    Vertex2d pointToAdd;
    
    xVariation = abs((int)(lastPoint.getX() - initialPoint.getX()));
    yVariation = abs((int)(lastPoint.getY() - initialPoint.getY()));
    
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
 * Generate the points for a circunference
 * @param circumference (Circumference*)
 * @param center {Vertex2d} - the center of the circumference
 * @param currentPoint {Vertex2d} - the current point
 */
void generateCircumferencePoints(Circumference *circumference, Vertex2d center, Vertex2d currentPoint) {
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
Circumference generateCircumferenceBresenham(Vertex2d center, int radius) {
    int currentX, currentY, d;
    Circumference circumference(radius);
    Circumference *reference = &circumference;
    Vertex2d currentPoint;
    
    currentPoint.setX(0);
    currentPoint.setY(radius);
    d = 1 - radius;
    
    generateCircumferencePoints(reference, center, currentPoint);
    
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

#endif /* bresenham_h */

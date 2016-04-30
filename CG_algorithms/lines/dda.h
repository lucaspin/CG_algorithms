/**
 * dda.h
 *
 * Library that contains the DDA algorithm for drawing lines
 * @author Lucas Pinheiro
 */

#ifndef dda_h
#define dda_h

#include "Line.hpp"
#include "../common/Vertex2d.hpp"

Line generateLineDDA(Vertex2d initialPoint, Vertex2d lastPoint);

/**
 * Display a line on the screen, using the DDA algorithm
 * @param initialPoint - the initial coordinate of the line
 * @param lastPoint - the last coordinate of the line
 */
Line generateLineDDA(Vertex2d initialPoint, Vertex2d lastPoint) {
    int xVariation, yVariation;
    float xIncrement, yIncrement;
    int numOfIterations, count;
    float currentX, currentY;
    
    Line line;
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

#endif /* dda_h */

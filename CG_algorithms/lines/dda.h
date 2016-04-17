/**
 * dda.h
 *
 * Library that contains the DDA algorithm for drawing lines
 * @author Lucas Pinheiro
 */

#ifndef dda_h
#define dda_h

void displayLineDDA(int initialX, int initialY, int finalX, int finalY);

/**
 * Display a line on the screen, using the DDA algorithm
 * @param initialX - the x coordinate of the first point
 * @param initialY - the y coordinate of the first point
 * @param finalX - the x coordinate of the second point
 * @param finalY - the y coordinate of the second point
 */
void displayLineDDA(int initialX, int initialY, int finalX, int finalY) {
    int xVariation, yVariation;
    float xIncrement, yIncrement;
    int numOfIterations, count;
    float currentX, currentY;
    
    xVariation = finalX - initialX;
    yVariation = finalY - initialY;
    
    if (abs(xVariation) > abs(yVariation)) {
        numOfIterations = abs(xVariation);
    } else {
        numOfIterations = abs(yVariation);
    }
    
    xIncrement = (float) xVariation / numOfIterations;
    yIncrement = (float) yVariation / numOfIterations;
    
    currentX = initialX;
    currentY = initialY;
    
    glBegin(GL_POINTS);
    glColor3f(255, 255, 255);
    glVertex3i(round(currentX), round(currentY), 0);
    glEnd();
    
    glBegin(GL_POINTS);
    for (count = 1; count < numOfIterations; count++) {
        currentX += xIncrement;
        currentY += yIncrement;
        glVertex3i(round(currentX), round(currentY), 0);
    }
    glEnd();
}

#endif /* dda_h */

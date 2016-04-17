/**
 * bresenham.h
 *
 * Library that contains bresenham algorithms for drawing lines and circumferences
 * @author Lucas Pinheiro
 */

#ifndef bresenham_h
#define bresenham_h

void displayLineBresenham(int initialX, int initialY, int finalX, int finalY);
void displayCircumferenceBresenham(int xCenter, int yCenter, int radius);
void printCircumferencePoints(int xCenter, int yCenter, int x, int y);

/**
 * Display a line on the screen, using the Bresenham algorithm
 * @param initialX - the x coordinate of the first point
 * @param initialY - the y coordinate of the first point
 * @param finalX - the x coordinate of the second point
 * @param finalY - the y coordinate of the second point
 */
void displayLineBresenham(int initialX, int initialY, int finalX, int finalY) {
    int xVariation, yVariation, currentX, currentY;
    int const1, const2, d, lastX;
    
    xVariation = abs(finalX - initialX);
    yVariation = abs(finalY - initialY);
    
    d = (2 * xVariation) - yVariation;
    const1 = 2 * xVariation;
    const2 = 2 * (yVariation - xVariation);
    
    if (initialX > finalX) {
        currentX = finalX;
        currentY = finalY;
        lastX = initialX;
    } else {
        currentX = initialX;
        currentY = initialY;
        lastX = finalX;
    }
    
    glBegin(GL_POINTS);
    glColor3f(255, 255, 255);
    glVertex3i(currentX, currentY, 0);
    glEnd();
    
    glBegin(GL_POINTS);
    
    while (currentX < lastX) {
        currentX++;
        if (d < 0) {
            d += const1;
        } else {
            currentY++;
            d += const2;
        }
        glVertex3i(currentX, currentY, 0);
    }
    
    glEnd();
}

/**
 * Print the points for a circunference for some x coordinate and y coordinate
 * @param xCenter the x coordinate of the center of the circumference
 * @param yCenter the y coordinate of the center of the circumference
 * @param x the
 */
void printCircumferencePoints(int xCenter, int yCenter, int x, int y) {
    glBegin(GL_POINTS);
    glColor3f(255, 255, 255);
    glVertex3i(xCenter + x, yCenter + y, 0);
    glVertex3i(xCenter + y, yCenter + x, 0);
    glVertex3i(xCenter + y, yCenter - x, 0);
    glVertex3i(xCenter + x, yCenter - y, 0);
    glVertex3i(xCenter - x, yCenter - y, 0);
    glVertex3i(xCenter - y, yCenter - x, 0);
    glVertex3i(xCenter - y, yCenter + x, 0);
    glVertex3i(xCenter - x, yCenter + y, 0);
    glEnd();
}

/**
 * Display a circumference on the screen, using the Bresenham algorithm for circumferences
 * @param xCenter the x coordinate of the center of the circumference
 * @param yCenter the y coordinate of the center of the circumference
 * @param radius the radius of the circumference
 */
void displayCircumferenceBresenham(int xCenter, int yCenter, int radius) {
    int currentX, currentY, d;
    
    currentX = 0;
    currentY = radius;
    d = 1 - radius;
    
    printCircumferencePoints(xCenter, yCenter, currentX, currentY);
    
    while (currentX < currentY) {
        if (d < 0) {
            d = d + (2 * currentX) + 3;
        } else {
            d = d + 2 * (currentX - currentY) + 5;
            currentY -= 1;
        }
        
        currentX++;
        printCircumferencePoints(xCenter, yCenter, currentX, currentY);
    }
}

#endif /* bresenham_h */

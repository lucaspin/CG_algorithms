/**
 * Program that fills a polygon using Scan Line Algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include <iostream>
#include <list>
#include <map>

// Include OpenGL and freeglut
#include <math.h>
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include "GL/freeglut.h"

#include "polygons/EdgesTable.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_TITLE "Scan Line algorithm"

void onDisplay();
void centerOnScreen();

// Define the window position on screen
int window_x;
int window_y;

int main(int argc, char **argv) {
    
    // Initialize glut
    glutInit(&argc, argv);
    
    // Centralize the window
    centerOnScreen();
    
    // Set some options for the window and create it
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow(WINDOW_TITLE);
    
    // Set the callback functions
    glutDisplayFunc(onDisplay);
    
    // Start glut event processing loop
    glutMainLoop();
    
    return 0;
}

void onDisplay() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    
    // The list of points that will form the polygon
    list<Vertex2d> listOfCoordinates;
    
    // The list of active edges
    list<PolygonEdge> activeEdges;
    
    // Create some points
    Vertex2d pointA(40, 60);
    Vertex2d pointB(140, 20);
    Vertex2d pointC(260, 100);
    Vertex2d pointD(260, 200);
    Vertex2d pointE(140, 140);
    Vertex2d pointF(40, 180);
    
    // Create the list of points
    listOfCoordinates.push_back(pointA);
    listOfCoordinates.push_back(pointB);
    listOfCoordinates.push_back(pointC);
    listOfCoordinates.push_back(pointD);
    listOfCoordinates.push_back(pointE);
    listOfCoordinates.push_back(pointF);
    
    // Create the edges table
    EdgesTable edgesTable(listOfCoordinates);
    
    // Get the smaller y from the list of coordinates
    int scanLineY = min_element(listOfCoordinates.begin(), listOfCoordinates.end())->getY();
    
    // Move the list of key scanLineY to active edges and remove it from the edges table
    list<PolygonEdge> initialActiveEdges = edgesTable.getEdgesMap().at(scanLineY);
    activeEdges.merge(initialActiveEdges);
    edgesTable.removeEntryFromMap(scanLineY);
    
    // Make sure it is sorted already
    activeEdges.sort();
    
    while (!activeEdges.empty() || !edgesTable.isEmpty()) {
        
        // Draw the points
        glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 1.0);
        
        for (auto it = activeEdges.begin(); it != activeEdges.end(); it++) {
            // Get the next edge
            auto nextPolygon = next(it);
            
            // Get the extremes x coordinates
            int leftXValue = ceilf(it->getCurrentX());
            int rightXValue = floorf(nextPolygon->getCurrentX());
            
            // Plot all the points between the two extremes
            for (; leftXValue <= rightXValue; leftXValue++) {
                glVertex3i(leftXValue, scanLineY, 0);
            }
            
            // Make sure it goes on groups of two
            it++;
        }
        
        glEnd();
        
        // Increment the scan line y coordinate
        scanLineY++;
        
        // Remove the edges from the list that had been reached its maximmum y
        activeEdges.remove_if([scanLineY](const PolygonEdge edge){
            return edge.getMaxYCoordinate() == scanLineY;
        });
        
        for (auto it = activeEdges.begin(); it != activeEdges.end(); it++) {
            it->updateCurrentX();
        }
        
        // Make sure the list is sorted after the updates
        activeEdges.sort();
        
        // Move the list of key scanLineY to active edges and remove it from the edges table
        auto foundIt = edgesTable.getEdgesMap().find(scanLineY);
        
        if (foundIt != edgesTable.getEdgesMap().end()) {
            activeEdges.merge(foundIt->second);
            activeEdges.sort();
            edgesTable.removeEntryFromMap(scanLineY);
        }
    }
    
    glFlush();
    glutSwapBuffers();
}

/**
 * this function is responsible to set the x and y coordinates
 * such as the window gets centered
 */
void centerOnScreen() {
    window_x = (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2;
    window_y = (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2;
}
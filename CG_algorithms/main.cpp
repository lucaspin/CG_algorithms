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
#include "2D_transformations/Matrix2d.hpp"
#include "2D_transformations/TransformationMatrix.hpp"
#include "polygons/Polygon.hpp"
#include "lines/Line.hpp"
#include "lines/Circumference.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_TITLE "Computer Graphics Algorithms"

using namespace std;

void onDisplay();
void centerOnScreen();
Polygon generatePolygon();
void printGeometricFigure(GeometricFigure figure);
void transformationDemo();

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

void printGeometricFigure(GeometricFigure figure) {
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    
    for (Vertex2d point : figure.getPoints()) {
        glVertex3i(point.getX(), point.getY(), point.getZ() - 1);
    }
    
    glEnd();
}

void onDisplay() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    
    transformationDemo();
    
    glFlush();
    glutSwapBuffers();
}

void translatePolygonDemo() {
    // The list of points that will form the polygon
    list<Vertex2d> listOfCoordinates;
    
    // Create some points
    Vertex2d pointA(40, 60, 1.0f);
    Vertex2d pointB(140, 20, 1.0f);
    Vertex2d pointC(260, 100, 1.0f);
    Vertex2d pointD(260, 200, 1.0f);
    Vertex2d pointE(140, 140, 1.0f);
    Vertex2d pointF(40, 180, 1.0f);
    
    // Create the list of points
    listOfCoordinates.push_back(pointA);
    listOfCoordinates.push_back(pointB);
    listOfCoordinates.push_back(pointC);
    listOfCoordinates.push_back(pointD);
    listOfCoordinates.push_back(pointE);
    listOfCoordinates.push_back(pointF);
    
    Polygon polygon = Polygon::generatePolygon(listOfCoordinates);
    printGeometricFigure(polygon);
    polygon.translate(200, 200);
    printGeometricFigure(polygon);
}

void transformationDemo() {
    // The list of points that will form the polygon
    list<Vertex2d> listOfCoordinates;
    
    // Create some points
    Vertex2d pointA(50, 50, 1.0f);
    Vertex2d pointB(100, 50, 1.0f);
    Vertex2d pointC(100, 100, 1.0f);
    Vertex2d pointD(50, 100, 1.0f);
    
    // Create the list of points
    listOfCoordinates.push_back(pointA);
    listOfCoordinates.push_back(pointB);
    listOfCoordinates.push_back(pointC);
    listOfCoordinates.push_back(pointD);
    
    Polygon polygon = Polygon::generatePolygon(listOfCoordinates);
    printGeometricFigure(polygon);
    
    // Translation
    polygon.translate(100, 0);
    printGeometricFigure(polygon);
    
    // Scale
    polygon.translate(100, 200);
    polygon.scale(1.5f, 1.5f, 150, 150);
    printGeometricFigure(polygon);
    
    // Rotation
    polygon.translate(-100, 0);
    polygon.rotate(45.0f, 150, 150);
    printGeometricFigure(polygon);
}

/**
 * this function is responsible to set the x and y coordinates
 * such as the window gets centered
 */
void centerOnScreen() {
    window_x = (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2;
    window_y = (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2;
}
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
#include "common/CodedVertex2d.hpp"
#include "common/ViewportWindow.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_TITLE "Computer Graphics Algorithms"

using namespace std;

void onDisplay();
void centerOnScreen();
Polygon generatePolygon();
void printGeometricFigure(GeometricFigure figure);
void viewportDemo();
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

void onDisplay() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    
    viewportDemo();
    transformationDemo();
    
    glFlush();
    glutSwapBuffers();
}

void viewportDemo() {
    Vertex2d bottomLeftCorner(0.0f, 0.0f);
    Vertex2d topRightCorner(100.0f, 100.0f);
    ViewportWindow  vpw(bottomLeftCorner, topRightCorner);
    Line line1(1.0f, 1.0f, 99.0f, 99.0f);       // all inside
    Line line2(-1.0f, -1.0f, 101.0f, -1.0f);    // all outside
    Line line3(-10.0f, 70.0f, 50.0f, 105.0f);   // partially inside
    Line line4(-10.0f, 40.0f, 110.0f, 50.0f);   // partially inside
    //Line line5(-10.0f, 40.0f, 110.0f, 40.0f);       // partially inside (horizontal line)
    //Line line6(30.0f, -10.0f, 30.0f, 110.0f);       // partially inside (vertical line)
//    list<GeometricFigure> lineList;
//    lineList.push_back(line1);
//    lineList.push_back(line2);
//    lineList.push_back(line3);
//    lineList.push_back(line4);
    //lineList.push_back(line5);
    //lineList.push_back(line6);
//    vpw.clip(lineList);
    vpw.clipLine(line1);
    vpw.clipLine(line2);
    vpw.clipLine(line3);
    vpw.clipLine(line4);
}

void transformationDemo() {
    // The list of points that will form the polygon
    list<Vertex2d> listOfCoordinates;
    
    // Create some points
    Vertex2d pointA(50, 50);
    Vertex2d pointB(100, 50);
    Vertex2d pointC(100, 100);
    Vertex2d pointD(50, 100);
    
    // Create the list of points
    listOfCoordinates.push_back(pointA);
    listOfCoordinates.push_back(pointB);
    listOfCoordinates.push_back(pointC);
    listOfCoordinates.push_back(pointD);
    
    Polygon polygon = Polygon::generatePolygon(listOfCoordinates);
    polygon.GeometricFigure::plotPoints();
    
    // Translation
    polygon.translate(100, 0);
    polygon.GeometricFigure::plotPoints();
    
    // Scale
    polygon.translate(100, 200);
    polygon.scale(1.5f, 1.5f, 150, 150);
    polygon.GeometricFigure::plotPoints();
    
    // Rotation
    polygon.translate(-100, 0);
    polygon.rotate(45.0f, 150, 150);
    polygon.GeometricFigure::plotPoints();
}

/**
 * this function is responsible to set the x and y coordinates
 * such as the window gets centered
 */
void centerOnScreen() {
    window_x = (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2;
    window_y = (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2;
}
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
Polygon generateFilledPolygon();
void printGeometricFigure(GeometricFigure figure);
void viewportClipLineDemo();
void viewportClipPolygonDemo();
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
    
    viewportClipLineDemo();
    viewportClipPolygonDemo();
    //    transformationDemo();
    
    glFlush();
    glutSwapBuffers();
}

void viewportClipLineDemo() {
    Vertex2d bottomLeftCorner(100.0f, 100.0f);
    Vertex2d topRightCorner(200.0f, 200.0f);
    ViewportWindow vpw(bottomLeftCorner, topRightCorner);
    
    Vertex2d a(120.0f, 120.0f);
    Vertex2d b(150.0f, 150.0f);
    Vertex2d c(50.0f, 170.0f);
    Vertex2d d(140.0f, 250.0f);
    Vertex2d e(60.0f, 300.0f);
    Vertex2d f(250.0f, 190.0f);
    
    Line line1 = Line::generateLineDDA(a, b);       // all inside
    Line line2 = Line::generateLineDDA(c, e);    // all outside
    Line line3 = Line::generateLineDDA(c, b);   // partially inside
    Line line4 = Line::generateLineDDA(c, f);   // partially inside
    
    // Simulate the viewport borders
    Vertex2d topLeft(100.0f, 200.0f);
    Vertex2d topRight(200.0f, 200.0f);
    Vertex2d bottomLeft(100.0f, 100.0f);
    Vertex2d bottomRight(200.0f, 100.0f);
    list<Vertex2d> listPoligonViewPort;
    listPoligonViewPort.push_back(topLeft);
    listPoligonViewPort.push_back(bottomLeft);
    listPoligonViewPort.push_back(bottomRight);
    listPoligonViewPort.push_back(topRight);
    Polygon poligonViewPort = Polygon::generateNotFilledPolygon(listPoligonViewPort);
    poligonViewPort.GeometricFigure::plotPoints();

    vpw.clipLine(line1);
    vpw.clipLine(line2);
    vpw.clipLine(line3);
    vpw.clipLine(line4);
    
    //translating the "ViewPort" just for simulating the before and after clipping
    poligonViewPort.translate(0.0f, 150.0f);
    poligonViewPort.GeometricFigure::plotPoints();
    
    // Print the lines without clipping
    line1.translate(0.0f, 150.0f);
    line2.translate(0.0f, 150.0f);
    line3.translate(0.0f, 150.0f);
    line4.translate(0.0f, 150.0f);
    line1.plotPoints();
    line2.plotPoints();
    line3.plotPoints();
    line4.plotPoints();

    std::list<GeometricFigure*> clippedObjects = vpw.getVisibleObjects();
    std::list<GeometricFigure*>::const_iterator it;
    
    for (it = clippedObjects.begin(); it != clippedObjects.end(); it++) {
        Vertex2d initialPoint = static_cast<Line*>(*it)->getInitialPoint();
        Vertex2d finalPoint = static_cast<Line*>(*it)->getFinalPoint();
        Line line = Line::generateLineDDA(initialPoint, finalPoint);
        line.GeometricFigure::plotPoints();
    }
}

void viewportClipPolygonDemo() {
    // Simulate the viewport borders
    Vertex2d topLeft(300.0f, 200.0f);
    Vertex2d topRight(400.0f, 200.0f);
    Vertex2d bottomLeft(300.0f, 100.0f);
    Vertex2d bottomRight(400.0f, 100.0f);
    Line topLine = Line::generateLineDDA(topLeft, topRight);
    Line bottomLine = Line::generateLineDDA(bottomLeft, bottomRight);
    Line leftLine = Line::generateLineDDA(bottomLeft, topLeft);
    Line rightLine = Line::generateLineDDA(bottomRight, topRight);
    
    // Print the viewport
    topLine.GeometricFigure::plotPoints();
    bottomLine.GeometricFigure::plotPoints();
    leftLine.GeometricFigure::plotPoints();
    rightLine.GeometricFigure::plotPoints();

    // Draw some polygons
    Vertex2d a(320.0f, 120.0f);
    Vertex2d b(280.0f, 180.0f);
    Vertex2d c(350.0f, 230.0f);
    Vertex2d d(430.0f, 150.0f);
    
    list<Vertex2d> listPoligonViewPort;
    listPoligonViewPort.push_back(topLeft);
    listPoligonViewPort.push_back(bottomLeft);
    listPoligonViewPort.push_back(bottomRight);
    listPoligonViewPort.push_back(topRight);
    Polygon poligonViewPort = Polygon::generateNotFilledPolygon(listPoligonViewPort);
    
//    Vertex2d e(60.0f, 300.0f);POlygoon
//    Vertex2d f(250.0f, 190.0f);
    list<Vertex2d> listPolygon1;
    listPolygon1.push_back(a);
    listPolygon1.push_back(b);
    listPolygon1.push_back(c);
    listPolygon1.push_back(d);
    Polygon poligon1 = Polygon::generateFilledPolygon(listPolygon1);
    poligon1.GeometricFigure::plotPoints();
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
    
    Polygon polygon = Polygon::generateFilledPolygon(listOfCoordinates);
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
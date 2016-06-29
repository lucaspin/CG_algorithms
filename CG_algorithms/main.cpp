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
void timer(int value);

// Define the window position on screen
int window_x;
int window_y;
int angleToRotate = 0;
int variationX = 0;
float scaleVariation = 1.0;
bool isShrinking = true;

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
    
    glutTimerFunc(30, timer, 1);
    
    // Start glut event processing loop
    glutMainLoop();
    
    return 0;
}

void timer(int value) {
    if (angleToRotate != 360) {
        angleToRotate += 10;
    } else {
        angleToRotate = 10;
    }
    
    if (variationX <= 740) {
        variationX += 5;
    } else {
        variationX = 10;
    }
    
    if (scaleVariation >= 0.5f && isShrinking) {
        scaleVariation -= 0.01f;
        if (scaleVariation <= 0.5f) {isShrinking = !isShrinking;}
    } else {
        scaleVariation += 0.01f;
        if (scaleVariation >= 1.0f) {isShrinking = !isShrinking;}
    }
    
    glutPostRedisplay();
    glutTimerFunc(20, timer, 1);
}

void onDisplay() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
//    viewportClipLineDemo();
    viewportClipPolygonDemo();
    
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
}

void viewportClipLineDemo() {
    Vertex2d bottomLeftCorner(100.0f, 100.0f);
    Vertex2d topRightCorner(200.0f, 200.0f);
    ViewportWindow vpw(bottomLeftCorner, topRightCorner);
    
    Vertex2d a(120.0f, 120.0f);
    a.setRGBColors(0.4, 0.7, 0.2);
    Vertex2d b(150.0f, 150.0f);
    b.setRGBColors(0.4, 0.7, 0.2);
    Vertex2d c(50.0f, 170.0f);
    c.setRGBColors(0.4, 0.7, 0.2);
    Vertex2d d(140.0f, 250.0f);
    d.setRGBColors(0.4, 0.7, 0.2);
    Vertex2d e(60.0f, 300.0f);
    e.setRGBColors(0.4, 0.7, 0.2);
    Vertex2d f(250.0f, 190.0f);
    f.setRGBColors(0.4, 0.7, 0.2);
    
    Line line1 = Line::generateLineDDA(a, b);    // all inside
    Line line2 = Line::generateLineDDA(c, e);    // all outside
    Line line3 = Line::generateLineDDA(c, b);    // partially inside
    Line line4 = Line::generateLineDDA(c, f);    // partially inside
    
    // Simulate the viewport borders
    Vertex2d topLeft(100.0f, 200.0f);
    Vertex2d topRight(200.0f, 200.0f);
    Vertex2d bottomLeft(100.0f, 100.0f);
    Vertex2d bottomRight(200.0f, 100.0f);
    list<Vertex2d> listPolygonViewPort;
    listPolygonViewPort.push_back(topLeft);
    listPolygonViewPort.push_back(bottomLeft);
    listPolygonViewPort.push_back(bottomRight);
    listPolygonViewPort.push_back(topRight);
    Polygon polygonViewPort = Polygon::generateNotFilledPolygon(listPolygonViewPort);
    polygonViewPort.GeometricFigure::plotPoints();

    vpw.clipLine(line1);
    vpw.clipLine(line2);
    vpw.clipLine(line3);
    vpw.clipLine(line4);
    
    //translating the "ViewPort" just for simulating the before and after clipping
    polygonViewPort.translate(0.0f, 150.0f);
    polygonViewPort.GeometricFigure::plotPoints();
    
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
    Vertex2d topLeft(-100, 200.0f);
    topLeft.setRGBColors(0.4, 0.7, 0.2);
    Vertex2d topRight(0.0f, 200.0f);
    topRight.setRGBColors(0.4, 0.7, 0.2);
    Vertex2d bottomLeft(-100.0f, 100.0f);
    bottomLeft.setRGBColors(0.4, 0.7, 0.2);
    Vertex2d bottomRight(0.0f, 100.0f);
    bottomRight.setRGBColors(0.4, 0.7, 0.2);
    list<Vertex2d> listPolygonViewPort;
    listPolygonViewPort.push_back(topLeft);
    listPolygonViewPort.push_back(bottomLeft);
    listPolygonViewPort.push_back(bottomRight);
    listPolygonViewPort.push_back(topRight);
    Polygon polygonViewPort = Polygon::generateFilledPolygon(listPolygonViewPort);
    polygonViewPort.rotate(angleToRotate, -50.0, 150.0);
    polygonViewPort.translate(variationX, 0.0);
    polygonViewPort.GeometricFigure::plotPoints();
    
    Vertex2d topLeft2(-50, 250.0f);
    topLeft2.setRGBColors(0.9, 0.7, 0.2);
    Vertex2d topRight2(50.0f, 250.0f);
    topRight2.setRGBColors(0.9, 0.7, 0.2);
    Vertex2d bottomLeft2(-50.0f, 150.0f);
    bottomLeft2.setRGBColors(0.9, 0.7, 0.2);
    Vertex2d bottomRight2(50.0f, 150.0f);
    bottomRight2.setRGBColors(0.9, 0.7, 0.2);
    list<Vertex2d> listPolygonViewPort2;
    listPolygonViewPort2.push_back(topLeft2);
    listPolygonViewPort2.push_back(bottomLeft2);
    listPolygonViewPort2.push_back(bottomRight2);
    listPolygonViewPort2.push_back(topRight2);
    Polygon polygonViewPort2 = Polygon::generateFilledPolygon(listPolygonViewPort2);
    polygonViewPort2.rotate(angleToRotate, 0, 225.0);
    polygonViewPort2.translate(variationX, 0.0);
    polygonViewPort2.scale(scaleVariation, scaleVariation, 50, 150);
    polygonViewPort2.GeometricFigure::plotPoints();
    
    //translating the "ViewPort" just for simulating the before and after clipping
//    polygonViewPort.translate(0.0f, 150.0f);
//    polygonViewPort.GeometricFigure::plotPoints();
    
    // The ViewPort itslef
//    Vertex2d bottomLeftCorner(300.0f, 100.0f);
//    Vertex2d topRightCorner(400.0f, 200.0f);
//    ViewportWindow vpw(bottomLeftCorner, topRightCorner);
//
    // Draw some polygons
//    Vertex2d a(320.0f, 120.0f);
//    a.setRGBColors(0.7, 0.6, 0.8);
//    Vertex2d b(430.0f, 150.0f);
//    b.setRGBColors(0.7, 0.6, 0.8);
//    Vertex2d c(350.0f, 230.0f);
//    c.setRGBColors(0.7, 0.6, 0.8);
//    Vertex2d d(310.0f, 180.0f);
//    d.setRGBColors(0.7, 0.6, 0.8);
    
    // pushing in counter-clockwise orientation
//    list<Vertex2d> listPolygon1;
//    listPolygon1.push_back(a);
//    listPolygon1.push_back(b);
//    listPolygon1.push_back(c);
//    listPolygon1.push_back(d);
//    Polygon polygon1 = Polygon::generateFilledPolygon(listPolygon1);
//    polygon1.rotate(angleToRotate, 300.0, 150.0);
//    polygon1.GeometricFigure::plotPoints();
    
    // translating the polygon1 (test) for up and down
//    polygon1.translate(0.0f, 150.0f);
//    polygon1.GeometricFigure::plotPoints();
//    polygon1.translate(0.0f, -150.0f);
//    vpw.clipPolygon(polygon1);
//
//    std::list<GeometricFigure*> clippedObjects = vpw.getVisibleObjects();
//    std::list<GeometricFigure*>::const_iterator it;
//    
//    // Iterating and Plotting all objects in Viewport
//    for (it = clippedObjects.begin(); it != clippedObjects.end(); it++) {
//        Polygon *tempPolygon = static_cast<Polygon*>(*it);
//        Polygon newPolygon = Polygon::generateFilledPolygon(tempPolygon->getVerticesList());
//        newPolygon.GeometricFigure::plotPoints();
//    }
    
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
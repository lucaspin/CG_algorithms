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
    
    // heart mask S2 =)
    Vertex2d vertex1(0.0f, 0.0f);
    vertex1.setRGBColors(0.9, 0.0, 0.0);
    Vertex2d vertex2(10.0f, 0.0f);
    Vertex2d vertex3(10.0f, 10.0f);
    Vertex2d vertex4(20.0f, 10.0f);
    Vertex2d vertex5(20.0f, 20.0f);
    Vertex2d vertex6(30.0f, 20.0f);
    Vertex2d vertex7(30.0f, 30.0f);
    Vertex2d vertex8(40.0f, 30.0f);
    Vertex2d vertex9(40.0f, 40.0f);
    Vertex2d vertex10(50.0f, 40.0f);
    Vertex2d vertex11(50.0f, 50.0f);
    Vertex2d vertex12(60.0f, 50.0f);
    Vertex2d vertex13(60.0f, 60.0f);
    Vertex2d vertex14(70.0f, 60.0f);
    Vertex2d vertex15(70.0f, 80.0f);
    Vertex2d vertex16(60.0f, 80.0f);
    Vertex2d vertex17(60.0f, 90.0f);
    Vertex2d vertex18(50.0f, 90.0f);
    Vertex2d vertex19(50.0f, 100.0f);
    Vertex2d vertex20(30.0f, 100.0f);
    Vertex2d vertex21(30.0f, 90.0f);
    Vertex2d vertex22(20.0f, 90.0f);
    Vertex2d vertex23(20.0f, 80.0f);
    Vertex2d vertex24(10.0f, 80.0f);
    Vertex2d vertex25(10.0f, 70.0f);
    Vertex2d vertex26(0.0f, 70.0f);
    Vertex2d vertex27(0.0f, 80.0f);
    Vertex2d vertex28(-10.0f, 80.0f);
    Vertex2d vertex29(-10.0f, 90.0f);
    Vertex2d vertex30(-20.0f, 90.0f);
    Vertex2d vertex31(-20.0f, 100.0f);
    Vertex2d vertex32(-40.0f, 100.0f);
    Vertex2d vertex33(-40.0f, 90.0f);
    Vertex2d vertex34(-50.0f, 90.0f);
    Vertex2d vertex35(-50.0f, 80.0f);
    Vertex2d vertex36(-60.0f, 80.0f);
    Vertex2d vertex37(-60.0f, 60.0f);
    Vertex2d vertex38(-50.0f, 60.0f);
    Vertex2d vertex39(-50.0f, 50.0f);
    Vertex2d vertex40(-40.0f, 50.0f);
    Vertex2d vertex41(-40.0f, 40.0f);
    Vertex2d vertex42(-30.0f, 40.0f);
    Vertex2d vertex43(-30.0f, 30.0f);
    Vertex2d vertex44(-20.0f, 30.0f);
    Vertex2d vertex45(-20.0f, 20.0f);
    Vertex2d vertex46(-10.0f, 20.0f);
    Vertex2d vertex47(-10.0f, 10.0f);
    Vertex2d vertex48(0.0f, 10.0f);

    
    // pushing the heart's vertices to a list
    list<Vertex2d> listPolygonViewPortHeart;
    listPolygonViewPortHeart.push_back(vertex1);
    listPolygonViewPortHeart.push_back(vertex2);
    listPolygonViewPortHeart.push_back(vertex3);
    listPolygonViewPortHeart.push_back(vertex4);
    listPolygonViewPortHeart.push_back(vertex5);
    listPolygonViewPortHeart.push_back(vertex6);
    listPolygonViewPortHeart.push_back(vertex7);
    listPolygonViewPortHeart.push_back(vertex8);
    listPolygonViewPortHeart.push_back(vertex9);
    listPolygonViewPortHeart.push_back(vertex10);
    listPolygonViewPortHeart.push_back(vertex11);
    listPolygonViewPortHeart.push_back(vertex12);
    listPolygonViewPortHeart.push_back(vertex13);
    listPolygonViewPortHeart.push_back(vertex14);
    listPolygonViewPortHeart.push_back(vertex15);
    listPolygonViewPortHeart.push_back(vertex16);
    listPolygonViewPortHeart.push_back(vertex17);
    listPolygonViewPortHeart.push_back(vertex18);
    listPolygonViewPortHeart.push_back(vertex19);
    listPolygonViewPortHeart.push_back(vertex20);
    listPolygonViewPortHeart.push_back(vertex21);
    listPolygonViewPortHeart.push_back(vertex22);
    listPolygonViewPortHeart.push_back(vertex23);
    listPolygonViewPortHeart.push_back(vertex24);
    listPolygonViewPortHeart.push_back(vertex25);
    listPolygonViewPortHeart.push_back(vertex26);
    listPolygonViewPortHeart.push_back(vertex27);
    listPolygonViewPortHeart.push_back(vertex28);
    listPolygonViewPortHeart.push_back(vertex29);
    listPolygonViewPortHeart.push_back(vertex30);
    listPolygonViewPortHeart.push_back(vertex31);
    listPolygonViewPortHeart.push_back(vertex32);
    listPolygonViewPortHeart.push_back(vertex33);
    listPolygonViewPortHeart.push_back(vertex34);
    listPolygonViewPortHeart.push_back(vertex35);
    listPolygonViewPortHeart.push_back(vertex36);
    listPolygonViewPortHeart.push_back(vertex37);
    listPolygonViewPortHeart.push_back(vertex38);
    listPolygonViewPortHeart.push_back(vertex39);
    listPolygonViewPortHeart.push_back(vertex40);
    listPolygonViewPortHeart.push_back(vertex41);
    listPolygonViewPortHeart.push_back(vertex42);
    listPolygonViewPortHeart.push_back(vertex43);
    listPolygonViewPortHeart.push_back(vertex44);
    listPolygonViewPortHeart.push_back(vertex45);
    listPolygonViewPortHeart.push_back(vertex46);
    listPolygonViewPortHeart.push_back(vertex47);
    listPolygonViewPortHeart.push_back(vertex48);

    // 1st heart
    Polygon heart = Polygon::generateFilledPolygon(listPolygonViewPortHeart);
    heart.translate(variationX, 0.0);
    heart.scale(scaleVariation, scaleVariation, 50, 150);
    heart.GeometricFigure::plotPoints();

    // 2nd hearth
    Polygon heart2 = Polygon::generateFilledPolygon(listPolygonViewPortHeart);
    heart2.translate(50.0f, 50.0f);
    heart2.translate(variationX, variationX);
    heart2.scale(1.3, 1.3, 0, 50);
    heart2.scale(scaleVariation, scaleVariation, 50, 150);
    heart2.GeometricFigure::plotPoints();
    
    // 3rd heart
    Polygon heart3 = Polygon::generateFilledPolygon(listPolygonViewPortHeart);
    heart3.translate(800.0f, 600.0f);
    heart3.translate(-variationX, -variationX);
    heart3.scale(1.1, 1.1, 0, 50);
    heart3.scale(scaleVariation, scaleVariation, 50, 150);
    heart3.GeometricFigure::plotPoints();
    
    // 4rd hearth
    Polygon heart4 = Polygon::generateFilledPolygon(listPolygonViewPortHeart);
    heart4.translate(800.0f, 50.0f);
    heart4.translate(-variationX, variationX);
    heart4.scale(0.6, 0.6, 0, 50);
    heart4.scale(scaleVariation, scaleVariation, 50, 150);
    heart4.GeometricFigure::plotPoints();
    
    // 5th hearth
    Polygon heart5 = Polygon::generateFilledPolygon(listPolygonViewPortHeart);
    heart5.translate(200.0f, 300.0f);
    heart5.translate(sin(variationX/10), 0);
    heart5.scale(1.4, 1.4, 0, 50);
    heart5.scale(scaleVariation, scaleVariation, 50, 150);
    heart5.GeometricFigure::plotPoints();
    
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
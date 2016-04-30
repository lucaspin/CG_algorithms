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

#include "lines/dda.h"
#include "lines/bresenham.h"
#include "polygons/EdgesTable.hpp"
#include "2D_transformations/Matrix2d.hpp"
#include "2D_transformations/TransformationMatrix.hpp"
#include "polygons/Polygon.hpp"
#include "lines/Line.hpp"
#include "lines/Circumference.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_TITLE "Scan Line algorithm"

using namespace std;

void onDisplay();
void centerOnScreen();
Polygon generatePolygon();
void printGeometricFigure(GeometricFigure figure);
void matrix2dDemo();
void transformationMatrixDemo();

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
        glVertex3i(point.getX(), point.getY(), point.getZ());
    }
    
    glEnd();
}

void onDisplay() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    
    // TODO: apply some kind of transformation

    glFlush();
    glutSwapBuffers();
}

Polygon generatePolygon() {
    // The list of points that will form the polygon
    list<Vertex2d> listOfCoordinates;
    
    // Create some points
    Vertex2d pointA(40, 60, 0);
    Vertex2d pointB(140, 20, 0);
    Vertex2d pointC(260, 100, 0);
    Vertex2d pointD(260, 200, 0);
    Vertex2d pointE(140, 140, 0);
    Vertex2d pointF(40, 180, 0);
    
    // Create the list of points
    listOfCoordinates.push_back(pointA);
    listOfCoordinates.push_back(pointB);
    listOfCoordinates.push_back(pointC);
    listOfCoordinates.push_back(pointD);
    listOfCoordinates.push_back(pointE);
    listOfCoordinates.push_back(pointF);
    
    // Create the edges table
    EdgesTable edgesTable(listOfCoordinates);
    return edgesTable.initScanLineAlgorithm();
}

void matrix2dDemo() {
    vector<float> m1Values = {1,1,1,2,2,2,3,3,3};
    vector<float> m2Values = {2,2,3,3,4,4,1,1,1};
    
    Matrix2d m1(m1Values);
    Matrix2d m2(m2Values);
    Matrix2d m3 = m1 * m2;
    
    m3.printMatrix2d();
}

void transformationMatrixDemo() {
    //Translate Matrix2d
    cout << "Translation matrix for dx = 4 and dy = 1" << endl;
    Matrix2d testTranslateMatrix;
    testTranslateMatrix = TransformationMatrix::getInstance()->translate(4.0f, 1.0f);
    testTranslateMatrix.printMatrix2d();
    
    //Rotate Matrix2d
    cout << "Rotation matrix of 30 degress around (8,10)" << endl;
    Matrix2d testRotateMatrix;
    testRotateMatrix = TransformationMatrix::getInstance()->rotate(30.0f, 8.0f, 10.0f);
    testRotateMatrix.printMatrix2d();
    
    //Scale Matrix2d
    cout << "Scale matrix of 40% around (6,8)" << endl;
    Matrix2d testScaleMatrix;
    testScaleMatrix = TransformationMatrix::getInstance()->scale(1.4f, 1.4f, 6.0f, 8.0f);
    testScaleMatrix.printMatrix2d();
}

/**
 * this function is responsible to set the x and y coordinates
 * such as the window gets centered
 */
void centerOnScreen() {
    window_x = (glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2;
    window_y = (glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2;
}
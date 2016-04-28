/**
 * TransformationMatrix.cpp
 * SINGLETON
 * Class that works as a singleton and delivers the transformation matrixes
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "TransformationMatrix.hpp"

// Private

// Global static pointer used to ensure a single instance of the class
TransformationMatrix* TransformationMatrix::instance = NULL;

TransformationMatrix* TransformationMatrix::getInstance() {
    if ( !instance ) {
        instance = new TransformationMatrix();
    }
    return instance;
}

/**
 * Translate using dx, dy
 * @param dx {float}, dy {float}
 * @return {Matrix2d}
 */
Matrix2d TransformationMatrix::translate(float dx, float dy) {
    vector<float> translateVector = {1,0,dx,   0,1,dy,  0,0,1};
    Matrix2d outputMatrix( translateVector );
    return outputMatrix;
}

/**
 * Translate using initial and final coordinates
 * @param xInitial {float}, yInitial {float}, xFinal {float}, yFinal {float}
 * @return {Matrix2d}
 */
Matrix2d TransformationMatrix::translate(float xInitial, float yInitial,
                                         float xFinal, float yFinal) {
    float dx = xFinal - xInitial;
    float dy = yFinal - yInitial;
    return translate(dx,dy);
}

/**
 * Rotatation Matrix2d using a CounterClockWise angle around a pivot coordinate
 * @param rotationAngle {float} - in degrees (CounterClockWise), xPivot {float}, yPivot {float}
 * @return {Matrix2d}
 */
Matrix2d TransformationMatrix::rotate(float rotationAngle, float xPivot, float yPivot) {
    
    float cosine = cos(rotationAngle*PI/180);
    float sine = sin(rotationAngle*PI/180);
    vector<float> rotateVector = { cosine, -sine ,0,
                                   sine,   cosine,0,
                                    0  ,0        ,1};
    Matrix2d translateToOriginMatrix = translate(-xPivot, -yPivot);
    Matrix2d rotateMatrix( rotateVector );
    Matrix2d translateFromOriginMatrix = translate(xPivot, yPivot);
    
    Matrix2d outputMatrix = translateFromOriginMatrix * rotateMatrix * translateToOriginMatrix;
    return outputMatrix;
}

/**
 * Scale Matrix2d using a scaleFactor in x and y, around a coordinate
 * @param xScaleFactor {float}, yScaleFactor {float}, x {float}, y {float}
 * @return {Matrix2d}
 */
Matrix2d TransformationMatrix::scale(float xScaleFactor, float yScaleFactor, float x, float y) {
    
    vector<float> scaleVector = {xScaleFactor, 0,0,     0,yScaleFactor,0,       0,0,1};
    
    Matrix2d translateToOriginMatrix = translate(-x, -y);
    Matrix2d rotateMatrix( scaleVector );
    Matrix2d translateFromOriginMatrix = translate(x, y);
    
    Matrix2d outputMatrix = translateFromOriginMatrix * scaleVector * translateToOriginMatrix;
    return outputMatrix;
}
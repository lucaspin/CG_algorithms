/**
 * TransformationMatrix.cpp
 * SINGLETON
 * Class that works as a singleton and delivers the transformation matrixes
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "TransformationMatrix.hpp"

using namespace std;

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
Matrix2d TransformationMatrix::getTranslationMatrix(float dx, float dy) {
    vector<float> translateVector = {1,  0,  dx,
                                     0,  1,  dy,
                                     0,  0,  1};
    Matrix2d outputMatrix( translateVector );
    return outputMatrix;
}

/**
 * Rotatation Matrix2d using a CounterClockWise angle around a pivot coordinate
 * @param rotationAngle {float} - in degrees (CounterClockWise), xPivot {float}, yPivot {float}
 * @return {Matrix2d}
 */
Matrix2d TransformationMatrix::getRotationMatrix(float rotationAngle, float xPivot, float yPivot) {
    
    float cosine = cos(rotationAngle*PI/180);
    float sine = sin(rotationAngle*PI/180);
    
    vector<float> rotateVector = {cosine, -sine ,  0,
                                  sine,    cosine, 0,
                                  0,       0,      1};
    
    Matrix2d translateToOriginMatrix = getTranslationMatrix(-xPivot, -yPivot);
    Matrix2d rotateMatrix(rotateVector);
    Matrix2d translateFromOriginMatrix = getTranslationMatrix(xPivot, yPivot);
    Matrix2d outputMatrix = translateFromOriginMatrix * rotateMatrix * translateToOriginMatrix;
    
    return outputMatrix;
}

/**
 * Scale Matrix2d using a scaleFactor in x and y, around a coordinate
 * @param xScaleFactor {float}, yScaleFactor {float}, x {float}, y {float}
 * @return {Matrix2d}
 */
Matrix2d TransformationMatrix::getScaleMatrix(float xScaleFactor, float yScaleFactor, float x, float y) {
    vector<float> scaleVector = {xScaleFactor, 0,            0,
                                 0,            yScaleFactor, 0,
                                 0,            0,            1};
    
    Matrix2d translateToOriginMatrix = getTranslationMatrix(-x, -y);
    Matrix2d rotateMatrix(scaleVector);
    Matrix2d translateFromOriginMatrix = getTranslationMatrix(x, y);
    Matrix2d outputMatrix = translateFromOriginMatrix * scaleVector * translateToOriginMatrix;
    
    return outputMatrix;
}

/**
 * Shear Matrix2d using a shearFactor in x and y, around a coordinate
 * @param xSshearFactor {float}, yShearFactor {float}, x {float}, y {float}
 * @return {Matrix2d}
 */
Matrix2d TransformationMatrix::getShearMatrix(float xShearFactor, float yShearFactor, float x, float y) {
    
    vector<float> shearVector = {1,            xShearFactor, 0,
                                 yShearFactor, 1,            0,
                                 0,            0,            1};
    
    Matrix2d translateToOriginMatrix = getTranslationMatrix(-x, -y);
    Matrix2d rotateMatrix(shearVector);
    Matrix2d translateFromOriginMatrix = getTranslationMatrix(x, y);
    Matrix2d outputMatrix = translateFromOriginMatrix * shearVector * translateToOriginMatrix;
    
    return outputMatrix;
}
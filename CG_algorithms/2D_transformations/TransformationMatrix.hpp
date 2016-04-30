/**
 * TransformationMatrix.hpp
 * SINGLETON
 * Class that works as a singleton and delivers the transformation matrixes
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef TransformationMatrix_hpp
#define TransformationMatrix_hpp
#define PI 3.14159265

#include <stdio.h>
#include <iostream>  /* std */
#include <vector>
#include <math.h>    /* sin and cos */

#include "Matrix2d.hpp"

class TransformationMatrix {

public:
    
    static TransformationMatrix* getInstance();
    Matrix2d getTranslationMatrix(float, float);
    Matrix2d getRotationMatrix(float, float, float);
    Matrix2d getScaleMatrix(float, float, float, float);
    Matrix2d getShearMatrix(float, float, float, float);
    Matrix2d getXMirrorMatrix();
    Matrix2d getYMirrorMatrix();
    
private:
    static TransformationMatrix* instance;
    TransformationMatrix() {};
};

#endif /* TransformationMatrix_hpp */

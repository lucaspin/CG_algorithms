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
using namespace std;

class TransformationMatrix {

public:
    
    static TransformationMatrix* getInstance();
    
    Matrix2d translate(float, float);
    Matrix2d translate(float, float, float, float);
    Matrix2d rotate(float, float, float);
    Matrix2d scale(float, float, float);
    Matrix2d mirrorX();
    Matrix2d mirrorY();

private:

    static TransformationMatrix* instance;
    TransformationMatrix() {};
   
};

#endif /* TransformationMatrix_hpp */

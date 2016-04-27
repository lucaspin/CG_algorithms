/**
 * Matrix2d.cpp
 * Class that represent a matrix used in 2d transformations.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef Matrix2d_hpp
#define Matrix2d_hpp

#include <stdio.h>
#include <iostream>  /* std */
#include <vector>
using namespace std;

class Matrix2d {
public:
    
    Matrix2d();
    Matrix2d( vector<float> );
    void initializeValues( vector<float> );
    Matrix2d identity();
    
    // Getters and Setters
    vector< vector<float> > getMatrix2d() const;
    float getElement(int, int) const;
    void setElement(int, int, float);
    
    void setMatrix2d( vector< vector<float> > );
    void printMatrix2d();  // Debug Purpose
    
    // Overloads
    Matrix2d operator+(const Matrix2d& other);
    Matrix2d operator-(const Matrix2d& other);
    Matrix2d operator*(const Matrix2d& other);
    
private:
    // the matrix itself, always 3x3
    vector<vector<float>> matrix;
};

#endif /* Matrix2d_hpp */

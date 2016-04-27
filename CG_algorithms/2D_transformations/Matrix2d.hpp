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
    
    // Getters and Setters
    vector< vector<float> > getMatrix2d();
    float getElement(int, int) const;
    void setElement(int, int, float);
    void setMatrix2d( vector< vector<float> > );
    void printMatrix2d();  // Debug Purpose
    
    // Overloads
    Matrix2d operator+(const Matrix2d& other);
    Matrix2d operator-(const Matrix2d& other);
    
private:
    // the matrix itself, always 3x3
    
    vector< vector<float> > matrix(3, vector<float> (3, 0) );
    
    // constructors used in the same order as described above:
//    std::vector<int> first;
//    std::vector<int> second (4,100);
//    std::vector<int> third (second.begin(),second.end());
//    std::vector<int> fourth (third);
};

#endif /* Matrix2d_hpp */

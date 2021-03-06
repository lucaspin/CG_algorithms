/**
 * Matrix2d.cpp
 * Class that represent a matrix used in 2d transformations.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef Matrix2d_hpp
#define Matrix2d_hpp

#include <vector>
#include "../common/GeometricFigure.hpp"

class Matrix2d {
public:
    
    Matrix2d();
    Matrix2d( std::vector<float> );
    void initializeValues( std::vector<float> );
    Matrix2d identity();
    
    // Getters and Setters
    std::vector< std::vector<float> > getMatrix2d() const;
    float getElement(int, int) const;
    void setElement(int, int, float);
    
    void setMatrix2d( std::vector< std::vector<float> > );
    void printMatrix2d();  // Debug Purpose
    
    // Overloads
    Matrix2d operator+(const Matrix2d& other);
    Matrix2d operator-(const Matrix2d& other);
    Matrix2d operator*(const Matrix2d& other);
    GeometricFigure operator*(const GeometricFigure& figure);
    Vertex2d operator*(const Vertex2d& point);
    
private:
    // the matrix itself, always 3x3
    std::vector< std::vector<float > > matrix;
};

#endif /* Matrix2d_hpp */

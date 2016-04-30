/**
 * Line.cpp
 * Class to represent a line.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef Line_hpp
#define Line_hpp

#include <vector>
#include "../common/Vertex2d.hpp"
#include "../common/GeometricFigure.hpp"
#include "../2D_transformations/Matrix2d.hpp"

class Line : public GeometricFigure {
public:
    Line(Vertex2d, Vertex2d);
    Vertex2d getInitialPoint() const;
    void setInitialPoint(Vertex2d);
    Vertex2d getFinalPoint() const;
    void setFinalPoint(Vertex2d);
    static Line generateLineBresenham(Vertex2d, Vertex2d);
    static Line generateLineDDA(Vertex2d, Vertex2d);
    void translate(float, float);
private:
    void applyTransformationMatrix(Matrix2d transformationMatrix);
    
    Vertex2d initialPoint;
    Vertex2d finalPoint;
};

#endif /* Line_hpp */

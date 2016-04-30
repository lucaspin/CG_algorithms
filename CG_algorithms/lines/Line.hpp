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

class Line : public GeometricFigure {
public:
    Line(Vertex2d, Vertex2d);
    Vertex2d getInitialPoint() const;
    void setInitialPoint(Vertex2d);
    Vertex2d getFinalPoint() const;
    void setFinalPoint(Vertex2d);
    static Line generateLineBresenham(Vertex2d, Vertex2d);
    static Line generateLineDDA(Vertex2d, Vertex2d);
private:
    Vertex2d initialPoint;
    Vertex2d finalPoint;
};

#endif /* Line_hpp */

/**
 * Polygon.cpp
 * Class to represent a polygon.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef Polygon_hpp
#define Polygon_hpp

#include <list>
#include "../2D_transformations/Matrix2d.hpp"
#include "../common/Vertex2d.hpp"
#include "../common/GeometricFigure.hpp"

class Polygon : public GeometricFigure {
public:
    Polygon(std::list<Vertex2d>);
    std::list<Vertex2d> getVerticesList() const;
    void setVerticesList(std::list<Vertex2d>);
    static Polygon generatePolygon(std::list<Vertex2d>);
    void translate(float, float);
    void scale(float, float, float, float);
    void rotate(float, float, float);
private:
    void applyTransformationMatrix(Matrix2d transformationMatrix);
    std::list<Vertex2d> vertices;
};

#endif /* Polygon_hpp */

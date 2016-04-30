/**
 * Polygon.cpp
 * Class to represent a polygon.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef Polygon_hpp
#define Polygon_hpp

#include <list>
#include "../common/Vertex2d.hpp"
#include "../common/GeometricFigure.hpp"

class Polygon : public GeometricFigure {
public:
    Polygon(std::list<Vertex2d>);
    std::list<Vertex2d> getVerticesList() const;
    void setVerticesList(std::list<Vertex2d>);
private:
    std::list<Vertex2d> vertices;
};

#endif /* Polygon_hpp */

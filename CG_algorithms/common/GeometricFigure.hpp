/**
 * GeometricFigure.hpp
 * Class to represent a geometric figure.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef GeometricFigure_hpp
#define GeometricFigure_hpp

#include <vector>
#include "../common/Vertex2d.hpp"

enum GeometricFigureType {LINE, POLYGON, CIRCUMFERENCE };

class GeometricFigure {
public:
    std::vector<Vertex2d> getPoints() const;
    void setPoints(std::vector<Vertex2d>);
    void addPoint(Vertex2d);
    void plotPoints();
    void setType(GeometricFigureType _type);
    GeometricFigureType getType();
protected:
    std::vector<Vertex2d> points;
    GeometricFigureType type;
};

#endif /* GeometricFigure_hpp */

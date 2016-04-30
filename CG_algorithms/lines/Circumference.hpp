/**
 * Circumference.hpp
 * Class to represent a circumference.
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef Circumference_hpp
#define Circumference_hpp

#include <vector>
#include "../common/Vertex2d.hpp"
#include "../common/GeometricFigure.hpp"

class Circumference : public GeometricFigure {
public:
    Circumference(int);
    void setRadius(int radius);
    int getRadius() const;
private:
    int radius;
};

#endif /* Circumference_hpp */
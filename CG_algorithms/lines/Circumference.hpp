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
    static Circumference generateCircumferenceBresenham(Vertex2d, int);
    void setRadius(int radius);
    int getRadius() const;
private:
    static void generateCircumferencePoints(Circumference*,Vertex2d, Vertex2d);
    int radius;
};

#endif /* Circumference_hpp */
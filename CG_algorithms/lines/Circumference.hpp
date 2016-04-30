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
#include "../2D_transformations/Matrix2d.hpp"

class Circumference : public GeometricFigure {
public:
    Circumference(Vertex2d, int);
    static Circumference generateCircumferenceBresenham(Vertex2d, int);
    void setRadius(int);
    int getRadius() const;
    Vertex2d getCenter() const;
    void setCenter(Vertex2d);
    void translate(float, float);
private:
    static void generateCircumferencePoints(Circumference*,Vertex2d, Vertex2d);
    void applyTransformationMatrix(Matrix2d transformationMatrix);
    int radius;
    Vertex2d center;
};

#endif /* Circumference_hpp */
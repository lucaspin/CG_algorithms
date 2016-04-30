/**
 * Vertex2d.hpp
 * Class that represent a coordinate in two dimensions. It is used
 * in the Scan Line algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef Vertex2d_hpp
#define Vertex2d_hpp

#include <list>
#include <math.h>

class Vertex2d {
public:
    
    Vertex2d();
    Vertex2d(float, float, float);
    float getX() const;
    float getY() const;
    float getZ() const;
    void setX(float);
    void setY(float);
    void setZ(float);
    bool operator<(const Vertex2d&) const;
    float magnitude() const;
    Vertex2d normalized() const;
    
private:
    float x;
    float y;
    float z;
};

#endif /* Vertex2d_hpp */

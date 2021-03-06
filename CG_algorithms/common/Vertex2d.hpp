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
    Vertex2d(float, float);
    float getX() const;
    float getY() const;
    float getZ() const;
    float getRed() const;
    float getGreen() const;
    float getBlue() const;
    void setX(float);
    void setY(float);
    void setZ(float);
    void setRed(float);
    void setGreen(float);
    void setBlue(float);
    void setRGBColors(float, float, float);
    bool operator<(const Vertex2d&) const;
    float magnitude() const;
    Vertex2d normalized() const;
    
private:
    float x;
    float y;
    float z;
    float red;
    float green;
    float blue;
};

#endif /* Vertex2d_hpp */

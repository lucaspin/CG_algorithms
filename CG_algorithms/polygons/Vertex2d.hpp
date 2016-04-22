
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

class Vertex2d {
public:
    
    Vertex2d(float, float);
    float getX() const;
    float getY() const;
    void setX(float);
    void setY(float);
    bool operator<(const Vertex2d&) const;
    float magnitude() const;
    Vertex2d normalized() const;  //instantiate a new Vector2 of magnitude 1
    
private:
    float x;
    float y;
};

#endif /* Vertex2d_hpp */
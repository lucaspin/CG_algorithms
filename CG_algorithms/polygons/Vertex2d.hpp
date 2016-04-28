
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
#include <math.h>           /* sqrt */
#include <vector>
using namespace std;

class Vertex2d {
public:
    
    Vertex2d();
    Vertex2d(float, float);
    void setVertex2d( vector<float> initialValues );
    float getX() const;
    float getY() const;
    void setX(float);
    void setY(float);
    bool operator<(const Vertex2d&) const;
    float magnitude() const;
    Vertex2d normalized() const;
    
private:
    vector<float> vertex;
};

#endif /* Vertex2d_hpp */
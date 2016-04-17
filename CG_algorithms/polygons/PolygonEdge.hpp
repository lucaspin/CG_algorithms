/**
 * PolygonEdge.hpp
 * Class that represent a edge of a polygon to be formed. It is used
 * in the Scan Line algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef PolygonEdge_hpp
#define PolygonEdge_hpp

class PolygonEdge {
public:
    
    PolygonEdge(int, int, int, int, float);
    float getCurrentX() const;
    int getMaxYCoordinate() const;
    int getXForMinY() const;
    int getMinYCoordinate() const;
    float getSlope() const;
    void setCurrentX(float);
    void setMaxYCoordinate(int);
    void setMinYCoordinate(int);
    void setXForMinY(int);
    void setSlope(float);
    void updateCurrentX();
    bool operator==(const PolygonEdge&) const;
    bool operator<(const PolygonEdge&) const;
    
private:
    
    float currentX;
    int minYCoordinate;
    int maxYCoordinate;
    int xForMinY;
    float slope;
};

#endif /* PolygonEdge_hpp */

/**
 * ViewportWindow.hpp
 * Class for the Viewport in pipeline 2d
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#ifndef ViewportWindow_hpp
#define ViewportWindow_hpp
#include "Vertex2d.hpp"
#include "GeometricFigure.hpp"
#include "CodedVertex2d.hpp"
#include <list>
#include "../lines/Line.hpp"
#include "../polygons/Polygon.hpp"
#include <iostream>

class ViewportWindow {
private:
    Vertex2d bottomLeftCorner;
    Vertex2d topRightCorner;
    std::list<GeometricFigure> visibleObjects;
    bool clipLineAcceptanceTest(CodedVertex2d _initialPoint, CodedVertex2d _finalPoint);
    bool clipLineRejectionTest(CodedVertex2d _initialPoint, CodedVertex2d _finalPoint);
public:
    ViewportWindow(Vertex2d _bottomLeftCorner, Vertex2d topRightCorner);
    void setBottomLeftCorner(Vertex2d _bottomLeftCorner);
    void setTopRightCorner(Vertex2d _TopRightCorner);
    Vertex2d getBottomLeftCorner();
    Vertex2d getTopRightCorner();
    // Method to make a triage of primites that will be clipped
    void clip(std::list<GeometricFigure> _objects);
    // Cohen-Sutherland algorithm to clip lines
    void clipLine(Line _line);
    // Sutherland-Hodgman algorithm to clip Filled Concave Polygons
    void clipPolygon(Polygon _polygon);
};


#endif /* ViewportWindow_hpp */

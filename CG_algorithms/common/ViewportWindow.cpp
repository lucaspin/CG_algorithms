/**
 * ViewportWindow.cpp
 * Class for the Viewport in pipeline 2d
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "ViewportWindow.hpp"

using namespace std;

/**
 * @constructor
 * @param _bottomLeftCorner {Vertex2d}
 * @param _topRightCorner {Vertex2d}
 */
ViewportWindow::ViewportWindow(Vertex2d _bottomLeftCorner, Vertex2d _topRightCorner) {
    this->setBottomLeftCorner(_bottomLeftCorner);
    this->setTopRightCorner(_topRightCorner);
}

/**
 * Setter for the bottomLeftCorner
 * @param _bottomLeftCorner {Vertex2d}
 */
void ViewportWindow::setBottomLeftCorner(Vertex2d _bottomLeftCorner) {
    this->bottomLeftCorner = _bottomLeftCorner;
}

/**
 * Setter for the topRightCorner
 * @param _topRightCorner {Vertex2d}
 */
void ViewportWindow::setTopRightCorner(Vertex2d _topRightCorner) {
    this->topRightCorner = _topRightCorner;
}

/**
 * Gets the bottomLeftCorner
 * @return {Vertex2d}
 */
Vertex2d ViewportWindow::getBottomLeftCorner() {
    return this->bottomLeftCorner;
}

/**
 * Gets the topRightCorner
 * @return {Vertex2d}
 */
Vertex2d ViewportWindow::getTopRightCorner() {
    return this->topRightCorner;
}

/**
 * This method encapsulate the clip pipeline stage
 * We pass different kinds of GeometricFigures (LINE, POLYGON, CIRCUMFERENCE)
 * and the methods redirect to the specific clip algorithm
 * @param _objects {list<GeometricFigure>}
 */
void ViewportWindow::clip(list<GeometricFigure> _objects) {
    list<GeometricFigure>::iterator it;
    for (it = _objects.begin(); it != _objects.end(); it++) {
        // Polygons
        switch (it->getType()) {
            case LINE: {
                // TODO review this part
                GeometricFigure* p = &*it;
                clipLine(*static_cast<Line*>(p));
                break;
            }
            case POLYGON: {
                // TODO review this part
                GeometricFigure* q = &*it;
                clipPolygon(*static_cast<Polygon*>(q));
                break;
            }
            case CIRCUMFERENCE: {
                // TODO
                cout << "Error!Circumference not implemented in ViewportWindow::clip" << endl;
                break;
            }
        }
    }
}

/**
 * This is a line clipping method that uses the Cohen-Sutherland algorithm
 * @param _line {Line}
 */
void ViewportWindow::clipLine(Line _line) {
    // TODO
}

/**
 * This is a polygon clipping method that uses the Sutherland-Hodgman algorithm
 * This only work for filled concave polygons
 * Convex polygons need to be converted to 2 or more concave polygons through
 * another method (not implemented)
 * @param _polygon {Polygon}
 */
void ViewportWindow::clipPolygon(Polygon _polygon) {
    // TODO
}


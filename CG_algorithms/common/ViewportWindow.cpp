/**
 * ViewportWindow.cpp
 * Class for the Viewport in pipeline 2d
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "ViewportWindow.hpp"

using namespace std;

// Acceptance - (initialRegionCode | finalRegionCode) == 0000
bool ViewportWindow::clipLineAcceptanceTest(CodedVertex2d _initialPoint, CodedVertex2d _finalPoint) {
    vector<bool> falseVector = {false, false, false, false};
    vector<bool> initialRegionCode = _initialPoint.getRegionCode();
    vector<bool> finalRegionCode = _finalPoint.getRegionCode();
    return ((initialRegionCode == falseVector) && (finalRegionCode == falseVector));
}

// Rejection - (initialRegionCode & finalRegionCode) != 0000
bool ViewportWindow::clipLineRejectionTest(CodedVertex2d _initialPoint, CodedVertex2d _finalPoint) {
    vector<bool> initialRegionCode = _initialPoint.getRegionCode();
    vector<bool> finalRegionCode = _finalPoint.getRegionCode();
    for (int i = 0; i < initialRegionCode.size(); i++) {
        if (initialRegionCode[i] && finalRegionCode[i]) {
            return true;
        }
    }
    return false;
}

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
                cout << "Error! Circumference not implemented in ViewportWindow::clip" << endl;
                break;
            }
        }
    }
}

/**
 * This is a line clipping method that uses the Cohen-Sutherland algorithm
 * @param _line {Line}
 */
// This method is temporally public for testing purposes
void ViewportWindow::clipLine(Line _line) {
    // references for the Viewport
    float xMin = this->getBottomLeftCorner().getX();
    float yMin = this->getBottomLeftCorner().getY();
    float xMax = this->getTopRightCorner().getX();
    float yMax = this->getTopRightCorner().getY();
    
    // determining the regionCode for the first line point
    float x1 = _line.getInitialPoint().getX();
    float y1 = _line.getInitialPoint().getY();
    
    CodedVertex2d initialPoint(x1, y1);
    if (y1 > yMax) initialPoint.setTopRegionCode(true);
    if (y1 < yMin) initialPoint.setBottomRegionCode(true);
    if (x1 > xMax) initialPoint.setRightRegionCode(true);
    if (x1 < xMin) initialPoint.setLeftRegionCode(true);
    
    // determining the regionCode for the last line point
    float x2 = _line.getFinalPoint().getX();
    float y2 = _line.getFinalPoint().getY();
    
    CodedVertex2d finalPoint(x2, y2);
    if (y2 > yMax) finalPoint.setTopRegionCode(true);
    if (y2 < yMin) finalPoint.setBottomRegionCode(true);
    if (x2 > xMax) finalPoint.setRightRegionCode(true);
    if (x2 < xMin) finalPoint.setLeftRegionCode(true);
    
    vector<bool> falseVector = {false, false, false, false};
    vector<bool> initialRegionCode = initialPoint.getRegionCode();
    vector<bool> finalRegionCode = finalPoint.getRegionCode();
    
    //Acceptance - (initialRegionCode | finalRegionCode) == 0000
    if (clipLineAcceptanceTest(initialPoint, finalPoint)) {
        visibleObjects.push_back(_line);
        return;
    }
    
    // Rejection - (initialRegionCode & finalRegionCode) != 0000
    if (clipLineRejectionTest(initialPoint, finalPoint)) {return;}
    
    /* After this Acceptance and Rejection tests above, we still have two possible scenarios:
    * Line (still) tottaly outside OR crossing the Viewport
    * (intersections need to be determined)
    */
    
    // (angular coefficient) m = deltaY/deltaX
    float m = (yMax - yMin)/(xMax - xMin);
    // reference for the clippedPoint
    Vertex2d clippedPoint;
    float x, y;
    
    // Doubt: which point will be clipped?
    //left limit clipping
    x = xMin;
    if (initialPoint.getLeftRegionCode()) {
        y = y1 + m * (x - x1);
        clippedPoint.setX(x);
        clippedPoint.setY(y);
        _line.setInitialPoint(clippedPoint);
        initialPoint.setLeftRegionCode(false);
        // Acceptance or Rejection
        if (clipLineAcceptanceTest(initialPoint, finalPoint)) {
            visibleObjects.push_back(_line);
            return;
        }
        if (clipLineRejectionTest(initialPoint, finalPoint)) {return;}
    }
    if (finalPoint.getLeftRegionCode()) {
        y = y1 - m * (x2 - x);
        clippedPoint.setX(x);
        clippedPoint.setY(y);
        _line.setFinalPoint(clippedPoint);
        finalPoint.setLeftRegionCode(false);
        // Acceptance or Rejection
        if (clipLineAcceptanceTest(initialPoint, finalPoint)) {
            visibleObjects.push_back(_line);
            return;
        }
        if (clipLineRejectionTest(initialPoint, finalPoint)) {return;}
    }
    // call Acceptance and Rejection
    
    
    // right limit clipping
    x = xMax;
    if (initialPoint.getRightRegionCode()) {
        y = y1 + m * (x - x1);
        clippedPoint.setX(x);
        clippedPoint.setY(y);
        _line.setInitialPoint(clippedPoint);
        initialPoint.setRightRegionCode(false);
        // Acceptance or Rejection
        if (clipLineAcceptanceTest(initialPoint, finalPoint)) {
            visibleObjects.push_back(_line);
            return;
        }
        if (clipLineRejectionTest(initialPoint, finalPoint)) {return;}
    }
    if (finalPoint.getRightRegionCode()) {
        y = y1 - m * (x2 - x);
        clippedPoint.setX(x);
        clippedPoint.setY(y);
        _line.setInitialPoint(clippedPoint);
        finalPoint.setRightRegionCode(false);
        // Acceptance or Rejection
        if (clipLineAcceptanceTest(initialPoint, finalPoint)) {
            visibleObjects.push_back(_line);
            return;
        }
        if (clipLineRejectionTest(initialPoint, finalPoint)) {return;}
    }
    
    // bottom limit clipping
    y = yMin;
    if (initialPoint.getBottomRegionCode()) {
        x = x2 - (y2 - y)/m;
        clippedPoint.setX(x);
        clippedPoint.setY(y);
        _line.setInitialPoint(clippedPoint);
        initialPoint.setBottomRegionCode(false);
        // Acceptance or Rejection
        if (clipLineAcceptanceTest(initialPoint, finalPoint)) {
            visibleObjects.push_back(_line);
            return;
        }
        if (clipLineRejectionTest(initialPoint, finalPoint)) {return;}
    if (finalPoint.getBottomRegionCode()) {
        x = x1 + (y - y1)/m;
        clippedPoint.setX(x);
        clippedPoint.setY(y);
        _line.setFinalPoint(clippedPoint);
        finalPoint.setBottomRegionCode(false);
        // Acceptance or Rejection
        if (clipLineAcceptanceTest(initialPoint, finalPoint)) {
            visibleObjects.push_back(_line);
            return;
        }
        if (clipLineRejectionTest(initialPoint, finalPoint)) {return;}
    }
    }
    
    // top limit clipping
    y = yMax;
    if (initialPoint.getTopRegionCode()) {
        x = x2 - (y2 - y)/m;
        clippedPoint.setX(x);
        clippedPoint.setY(y);
        _line.setInitialPoint(clippedPoint);
        initialPoint.setTopRegionCode(false);
        // Acceptance or Rejection
        if (clipLineAcceptanceTest(initialPoint, finalPoint)) {
            visibleObjects.push_back(_line);
            return;
        }
        if (clipLineRejectionTest(initialPoint, finalPoint)) {return;}
    if (finalPoint.getTopRegionCode()) {
        x = x1 + (y - y1)/m;
        clippedPoint.setX(x);
        clippedPoint.setY(y);
        _line.setFinalPoint(clippedPoint);
        finalPoint.setTopRegionCode(false);
        // Acceptance or Rejection
        if (clipLineAcceptanceTest(initialPoint, finalPoint)) {
            visibleObjects.push_back(_line);
            return;
        }
        if (clipLineRejectionTest(initialPoint, finalPoint)) {return;}
    }
    }
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


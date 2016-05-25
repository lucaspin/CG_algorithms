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
    float initialX = _line.getInitialPoint().getX();
    float initialY = _line.getInitialPoint().getY();
    
    CodedVertex2d initialCodedPoint(initialX, initialY);
    if (initialY > yMax) initialCodedPoint.setTopRegionCode(true);
    if (initialY < yMin) initialCodedPoint.setBottomRegionCode(true);
    if (initialX > xMax) initialCodedPoint.setRightRegionCode(true);
    if (initialX < xMin) initialCodedPoint.setLeftRegionCode(true);
    
    // determining the regionCode for the last line point
    float finalX = _line.getFinalPoint().getX();
    float finalY = _line.getFinalPoint().getY();
    
    CodedVertex2d finalCodedPoint(finalX, finalY);
    if (finalY > yMax) finalCodedPoint.setTopRegionCode(true);
    if (finalY < yMin) finalCodedPoint.setBottomRegionCode(true);
    if (finalX > xMax) finalCodedPoint.setRightRegionCode(true);
    if (finalX < xMin) finalCodedPoint.setLeftRegionCode(true);
    
    bool actionTaken = false;
    Vertex2d newPoint;
    
    while (!actionTaken) {
        // Acceptance - (initialRegionCode | finalRegionCode) == 0000
        if (clipLineAcceptanceTest(initialCodedPoint, finalCodedPoint)) {
            visibleObjects.push_back(&_line);
            actionTaken = true;
        }
        
        // Rejection - (initialRegionCode & finalRegionCode) != 0000
        if (!actionTaken && clipLineRejectionTest(initialCodedPoint, finalCodedPoint)) {
            actionTaken = true;
        }
        
        if (!actionTaken) {
            // Calculate the intersection
            float m = (finalY - initialY) / (finalX - initialX);
            float x1, y1;
            
            // TODO: figure out a better way to do this clipping
            
            // Left Clipping
            if (initialCodedPoint.getLeftRegionCode()) {
                x1 = xMin;
                y1 = finalY - m * (finalX - x1);
                newPoint.setX(x1);
                newPoint.setY(y1);
                initialCodedPoint.setLeftRegionCode(false);
                _line.setInitialPoint(newPoint);
                
            } else if (finalCodedPoint.getLeftRegionCode()) {
                x1 = xMin;
                y1 = finalY - m * (finalX - x1);
                newPoint.setX(x1);
                newPoint.setY(y1);
                finalCodedPoint.setLeftRegionCode(false);
                _line.setFinalPoint(newPoint);
            }
            
            // Right Clipping
            if (initialCodedPoint.getRightRegionCode()) {
                x1 = xMax;
                y1 = finalY - m * (finalX - x1);
                newPoint.setX(x1);
                newPoint.setY(y1);
                initialCodedPoint.setRightRegionCode(false);
                _line.setInitialPoint(newPoint);
            } else if (finalCodedPoint.getRightRegionCode()) {
                x1 = xMax;
                y1 = finalY - m * (finalX - x1);
                newPoint.setX(x1);
                newPoint.setY(y1);
                finalCodedPoint.setRightRegionCode(false);
                _line.setFinalPoint(newPoint);
            }
            
            // Bottom Clipping
            if (initialCodedPoint.getBottomRegionCode()) {
                y1 = yMin;
                x1 = finalX - ((finalY - y1) / m);
                newPoint.setX(x1);
                newPoint.setY(y1);
                initialCodedPoint.setBottomRegionCode(false);
                _line.setInitialPoint(newPoint);
            } else if (finalCodedPoint.getBottomRegionCode()) {
                y1 = yMin;
                x1 = finalX - ((finalY - y1) / m);
                newPoint.setX(x1);
                newPoint.setY(y1);
                finalCodedPoint.setBottomRegionCode(false);
                _line.setFinalPoint(newPoint);
            }
            
            // Top Clipping
            if (initialCodedPoint.getTopRegionCode()) {
                y1 = yMax;
                x1 = finalX - ((finalY - y1) / m);
                newPoint.setX(x1);
                newPoint.setY(y1);
                initialCodedPoint.setTopRegionCode(false);
                _line.setInitialPoint(newPoint);
            } else if (finalCodedPoint.getTopRegionCode()) {
                y1 = yMax;
                x1 = finalX - ((finalY - y1) / m);
                newPoint.setX(x1);
                newPoint.setY(y1);
                finalCodedPoint.setTopRegionCode(false);
                _line.setFinalPoint(newPoint);
            }
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

std::list<GeometricFigure*> ViewportWindow::getVisibleObjects() {
    return this->visibleObjects;
}


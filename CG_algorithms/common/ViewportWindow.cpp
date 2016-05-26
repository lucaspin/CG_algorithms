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
 * Getter for the currently visible objects of the window.
 * @return {list<GeometricFigure*>}
 */
std::list<GeometricFigure*> ViewportWindow::getVisibleObjects() {
    return this->visibleObjects;
}

/**
 * Method to determine if a line is entirely inside the viewport window.
 * If that occurs, both of its points region codes should be 0000.
 * @param _initialPoint {CodedVertex2d}
 * @param _finalPoint {CodedVertex2d}
 * @return {bool}
 */
bool ViewportWindow::clipLineAcceptanceTest(CodedVertex2d _initialPoint, CodedVertex2d _finalPoint) {
    vector<bool> falseVector = {false, false, false, false};
    vector<bool> initialRegionCode = _initialPoint.getRegionCode();
    vector<bool> finalRegionCode = _finalPoint.getRegionCode();
    return ((initialRegionCode == falseVector) && (finalRegionCode == falseVector));
}

/**
 * Method to determine if a line is entirely outside the viewport window.
 * If that occurs, at least one region code from its points should be true.
 * @param _initialPoint {CodedVertex2d}
 * @param _finalPoint {CodedVertex2d}
 * @return {bool}
 */
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
 * This method encapsulate the clip pipeline stage
 * We pass different kinds of GeometricFigures (LINE, POLYGON, CIRCUMFERENCE)
 * and the method redirects to the specific clipping algorithm.
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
 * This is a line clipping method that uses the Cohen-Sutherland algorithm.
 * This method is temporally public for testing purposes.
 * @param _line {Line}
 */
void ViewportWindow::clipLine(Line _line) {
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
        if (clipLineAcceptanceTest(initialCodedPoint, finalCodedPoint)) {
            visibleObjects.push_back(&_line);
            actionTaken = true;
        }
        
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
 * This is a polygon clipping method that uses the Sutherland-Hodgman algorithm.
 * This only work for convex polygons.
 * Concave polygons need to be converted to 2 or more concave polygons through
 * another method (not implemented).
 * @param _polygon {Polygon}
 */
void ViewportWindow::clipPolygon(Polygon _polygon) {
    float xMin = this->getBottomLeftCorner().getX();
    float yMin = this->getBottomLeftCorner().getY();
    float xMax = this->getTopRightCorner().getX();
    float yMax = this->getTopRightCorner().getY();
    
    std::list<Vertex2d> listPolygon = _polygon.getVerticesList();
    std::list<Vertex2d>::const_iterator it;
    std::list<CodedVertex2d> listCodedVertex2d;
    
    // converting list<Vertex2d> in list<CodedVertex2d>, and determining the regionCodes
    for (it = listPolygon.begin(); it != listPolygon.end(); it++) {
        auto vertex = *it;
        float x = vertex.getX();
        float y = vertex.getY();
        CodedVertex2d tempCodedPoint(vertex.getX(), vertex.getY());
        if (y > yMax) tempCodedPoint.setTopRegionCode(true);
        if (y < yMin) tempCodedPoint.setBottomRegionCode(true);
        if (x > xMax) tempCodedPoint.setRightRegionCode(true);
        if (x < xMin) tempCodedPoint.setLeftRegionCode(true);
        listCodedVertex2d.push_back(tempCodedPoint);
    }
    
    std::list<CodedVertex2d>::const_iterator itCoded;
    
    for (itCoded = listCodedVertex2d.begin(); itCoded != listCodedVertex2d.end(); itCoded++) {
        auto nextVertice = next(itCoded);
        if (nextVertice == listCodedVertex2d.end()) {nextVertice = listCodedVertex2d.begin();}

        //bool actionTaken = false;
        //Vertex2d newPoint;
        
        // while (!actionTaken) {
        //if (clipLineAcceptanceTest(*itCoded, *nextVertice)) {
                //actionTaken = true;
                //   }
            if (/*!actionTaken && */clipLineRejectionTest(*itCoded, *nextVertice)) {
                listCodedVertex2d.erase(itCoded, nextVertice);
                //actionTaken = true;
            }
        // }
    }
    
    std::list<Vertex2d>listClippedVertex2d;
    
    // converting list<CodedVertex2d> in list<Vertex2d> to output polygon
    for (itCoded = listCodedVertex2d.begin(); itCoded != listCodedVertex2d.end(); itCoded++) {
        auto tempCodedVertex2d = *itCoded;
        Vertex2d tempVertex2d(tempCodedVertex2d.getX(), tempCodedVertex2d.getY());
        listClippedVertex2d.push_back(tempVertex2d);
    }

    Polygon clippedPolygon = *new Polygon(listClippedVertex2d);
    visibleObjects.push_back(&clippedPolygon);
}

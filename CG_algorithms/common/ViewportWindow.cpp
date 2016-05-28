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
 * Method that determines if a polygon edge is entirely inside a SPECIFIC Limit (by its index) of the viewport.
 * @param _initialPoint {CodedVertex2d}
 * @param _finalPoint {CodedVertex2d}
 * @param index {int} - index of the RegionCode that will be checked (0 Top, 1 Bottom, 2 Right, 3 Left)
 */
bool ViewportWindow::isEdgeInsideLimitByIndex(CodedVertex2d _initialPoint, CodedVertex2d _finalPoint, int index) {
    return !(_initialPoint.getRegionCodeByIndex(index) || _finalPoint.getRegionCodeByIndex(index));
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
    
    list<Vertex2d> polygonVertices = _polygon.getVerticesList();
    list<CodedVertex2d> codedPolygonVertices;
    
    // We must convert the list of Vertex2d vertices to CodedVertex2d before do the actual clipping
    for (auto it = polygonVertices.begin(); it != polygonVertices.end(); it++) {
        float x = it->getX();
        float y = it->getY();
        CodedVertex2d codedPoint(x, y);
        
        if (y > yMax) codedPoint.setTopRegionCode(true);
        if (y < yMin) codedPoint.setBottomRegionCode(true);
        if (x > xMax) codedPoint.setRightRegionCode(true);
        if (x < xMin) codedPoint.setLeftRegionCode(true);
        
        codedPolygonVertices.push_back(codedPoint);
    }

    // This is a counter to keep track of the boundaries
    int counter = 0;
    
    list<CodedVertex2d> newVertices;
    
    // We must do the clipping until all the limits has been clipped
    while (counter < 4) {
        
        // Iterate through all the vertices
        for (auto it = codedPolygonVertices.begin(); it != codedPolygonVertices.end(); it++) {
            auto nextVertice = next(it);
                
            // We need to close the polygon
            if (nextVertice == codedPolygonVertices.end()) {
                nextVertice = codedPolygonVertices.begin();
            }
            
            // If polygon's edge is not totally inside the viewport, we must calculate the intersect
            if (!this->isEdgeInsideLimitByIndex(*it, *nextVertice, counter)) {
                CodedVertex2d newInitialVertice;
                CodedVertex2d newFinalVertice;
                    
                float x1 = 0.0, y1 = 0.0, m = 0.0;
                float nextVerticeX = nextVertice->getX();
                float nextVerticeY = nextVertice->getY();
                    
                m = (nextVertice->getY() - it->getY()) / (nextVertice->getX() - it->getX());
                    
                if (it->getRegionCodeByIndex(counter)) {
                    switch (counter) {
                        case 0: // Top clipping
                            x1 = nextVerticeX - ((nextVerticeY - yMax) / m);
                            y1 = yMax;
                            newInitialVertice.setTopRegionCode(false);
                            break;
                                
                        case 1: // Bottom clipping
                            x1 = nextVerticeX - ((nextVerticeY - yMin) / m);
                            y1 = yMin;
                            newInitialVertice.setBottomRegionCode(false);
                            break;
                            
                        case 2: // Right clipping
                            x1 = xMax;
                            y1 = nextVerticeY - m * (nextVerticeX - xMax);
                            newInitialVertice.setRightRegionCode(false);
                            break;
                                
                        case 3: // Left clipping
                            x1 = xMin;
                            y1 = nextVerticeY - m * (nextVerticeX - xMin);
                            newInitialVertice.setLeftRegionCode(false);
                            break;
                    }
                        
                    newInitialVertice.setX(x1);
                    newInitialVertice.setY(y1);
                    newVertices.push_back(newInitialVertice);
                } else if (nextVertice->getRegionCodeByIndex(counter)) {
                    switch (counter) {
                        case 0: // Top clipping
                            x1 = nextVerticeX - ((nextVerticeY - yMax) / m);
                            y1 = yMax;
                            break;
                                
                        case 1: // Bottom clipping
                            x1 = nextVerticeX - ((nextVerticeY - yMin) / m);
                            y1 = yMin;
                            break;
                                
                        case 2: // Right clipping
                            x1 = xMax;
                            y1 = nextVerticeY - m * (nextVerticeX - xMax);
                            break;
                                
                        case 3: // Left clipping
                            x1 = xMin;
                            y1 = nextVerticeY - m * (nextVerticeX - xMin);
                            break;
                    }
                        
                    newFinalVertice.setX(x1);
                    newFinalVertice.setY(y1);
                    newVertices.push_back(newFinalVertice);
                }
            } else {
                newVertices.push_back(*nextVertice);
            }
        }
        
        codedPolygonVertices = newVertices;
        newVertices.clear();
        
        counter++;
    }
    
    Polygon *clippedPolygon = new Polygon(codedPolygonVertices);
    this->visibleObjects.push_back(clippedPolygon);
}

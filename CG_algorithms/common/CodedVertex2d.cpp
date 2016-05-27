/**
 * CodedVertex2d.cpp
 * We extend this class from Vertex2d, adding a regionCode field,
 * to implement the Cohen-Sutherland algorithm
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "CodedVertex2d.hpp"

using namespace std;

/**
 * Constructor of the class
 */
CodedVertex2d::CodedVertex2d():Vertex2d() {
    vector<bool> regionCode = {false, false, false, false};
    this->setRegionCode(regionCode);
}

/**
 * Constructor of the class
 * @param {float x}
 * @param {float y}
 * @param {float z}
 */
CodedVertex2d::CodedVertex2d(float x, float y, float z):Vertex2d(x, y, z) {
    vector<bool> regionCode = {false, false, false, false};
    this->setRegionCode(regionCode);
}

/**
 * Constructor of the class
 * @param {float x}
 * @param {float y}
 */
CodedVertex2d::CodedVertex2d(float x, float y):Vertex2d(x, y) {
    vector<bool> regionCode = {false, false, false, false};
    this->setRegionCode(regionCode);
}

/**
 * Setter for the RegionCode
 * @param _regionCode {vector<bool>}
 */
void CodedVertex2d::setRegionCode(vector<bool> _regionCode) {
    this->regionCode = _regionCode;
}

/**
 * Get the RegionCode
 * @return {vector<bool>}
 */
vector<bool> CodedVertex2d::getRegionCode() {
    return this->regionCode;
}


/**
 * Setter for the regionCode (top)
 * @param _state {bool}
 */
void CodedVertex2d::setTopRegionCode(bool _state) {
    this->regionCode[0] = _state;
}

/**
 * Setter for the regionCode (bottom)
 * @param _state {bool}
 */
void CodedVertex2d::setBottomRegionCode(bool _state) {
    this->regionCode[1] = _state;
}

/**
 * Setter for the regionCode (right)
 * @param _state {bool}
 */
void CodedVertex2d::setRightRegionCode(bool _state) {
    this->regionCode[2] = _state;
}

/**
 * Setter for the regionCode (left)
 * @param _state {bool}
 */
void CodedVertex2d::setLeftRegionCode(bool _state) {
    this->regionCode[3] = _state;
}

/**
 * Get the regionCode (top)
 * @return {bool}
 */
bool CodedVertex2d::getTopRegionCode() {
    return this->regionCode[0];
}

/**
 * Get the regionCode (bottom)
 * @return {bool}
 */
bool CodedVertex2d::getBottomRegionCode() {
    return this->regionCode[1];
}

/**
 * Get the regionCode (right)
 * @return {bool}
 */
bool CodedVertex2d::getRightRegionCode() {
    return this->regionCode[2];
}

/**
 * Get the regionCode (left)
 * @return {bool}
 */
bool CodedVertex2d::getLeftRegionCode() {
    return this->regionCode[3];
}

/**
 * Get a region code by its index
 * @param index {int}
 * @return {bool} the region code for the specified index 
 */
bool CodedVertex2d::getRegionCodeByIndex(int index) {
    return this->regionCode[index];
}

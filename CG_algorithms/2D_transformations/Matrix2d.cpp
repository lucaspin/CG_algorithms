/**
 * Matrix2d.hpp
 * Class that represent a matrix used in 2d transformations.
 * This is always a 3x3 Matrix by definition
 * @author Lucas Pinheiro (@lucaspin)
 * @author Dalton Lima (@daltonbr)
 */

#include "Matrix2d.hpp"

/**
 * @default constructor
 */
Matrix2d::Matrix2d() {
    vector<float> initialValues = {0,0,0,0,0,0,0,0,0};
    initializeValues(initialValues);
}

/**
 * @constructor
 * @param {vector<float>}
 */
Matrix2d::Matrix2d( vector<float> initialValues) {
    initializeValues(initialValues);
}

void Matrix2d::initializeValues( vector<float> initialValues){
    int initialValuesIndex = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++, initialValuesIndex++) {
            this->matrix[row][col] = initialValues[initialValuesIndex];
        }
    }
}

vector< vector<float> > Matrix2d::getMatrix2d() {
    return this->matrix;
}

/**
 * Getter for an arbitrary element
 */
float Matrix2d::getElement(int row, int col) const {
    return this->matrix[row][col];
}

/**
 * Setter for an arbitrary element
 */
void Matrix2d::setElement(int row, int col, float newValue) {
    this->matrix[row][col] = newValue;
}

/**
 * Setter for the entire Matrix2d
 */
void Matrix2d::setMatrix2d( vector< vector<float> > newValues ) {
    this->matrix = newValues;
}

/**
 * printMatrix2d - just for Debug purposes
 */
void Matrix2d::printMatrix2d() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << this->matrix[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Overload handler for the plus operator
 * @param {Matrix2d&}
 * @return {Matrix2d}
 */
Matrix2d Matrix2d::operator+(const Matrix2d& secondMatrix) {
    Matrix2d outputMatrix;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            outputMatrix.matrix[i][j] = this->matrix[i][j] + secondMatrix.matrix[i][j];
        }
    }
    return outputMatrix;
}

/**
 * Overload handler for the minus operator
 * @param {Matrix2d&}
 * @return {Matrix2d}
 */
Matrix2d Matrix2d::operator-(const Matrix2d& secondMatrix) {
    Matrix2d outputMatrix;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            outputMatrix.matrix[i][j] = this->matrix[i][j] - secondMatrix.matrix[i][j];
        }
    }
    return outputMatrix;
}












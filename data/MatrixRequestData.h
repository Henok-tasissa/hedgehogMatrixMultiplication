//
// Created by henok on 6/16/19.
//

#ifndef MATRIXMULTIPLICATION_MATRIXREQUESTDATA_H
#define MATRIXMULTIPLICATION_MATRIXREQUESTDATA_H

#include "hedgehog.h"
class MatrixRequestData {
public:
    MatrixRequestData(size_t row, size_t col, char type) : row(row), col(col), type(type) {}

    size_t getRow() const {
        return row;
    }
    size_t getCol() const {
        return col;
    }
    char getType() const {
        return type;
    }

private:
    size_t row;
    size_t col;
    char type;
};

#endif //MATRIXMULTIPLICATION_MATRIXREQUESTDATA_H

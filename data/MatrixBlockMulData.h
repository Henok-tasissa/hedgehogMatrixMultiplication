//
// Created by henok on 6/17/19.
//

#ifndef MATRIXMULTIPLICATION_MATRIXBLOCKMULDATA_H
#define MATRIXMULTIPLICATION_MATRIXBLOCKMULDATA_H


#include "./MatrixAdata.h"
#include "./MatrixBdata.h"

class MatrixBlockMulData{
public:

    MatrixBlockMulData(const std::shared_ptr<MatrixAdata<int *>> &matrixA,
                       const std::shared_ptr<MatrixBdata<int *>> &matrixB) :
            matrixA(matrixA), matrixB(matrixB) {}

    const std::shared_ptr<MatrixAdata<int *>> &getMatrixA() const {
        return matrixA;
    }
    const std::shared_ptr<MatrixBdata<int *>> &getMatrixB() const {
        return matrixB;
    }


private:
    std::shared_ptr<MatrixAdata<int *>> matrixA;
    std::shared_ptr<MatrixBdata<int *>> matrixB;
};


#endif //MATRIXMULTIPLICATION_MATRIXBLOCKMULDATA_H

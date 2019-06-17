//
// Created by henok on 6/17/19.
//

#ifndef MATRIXMULTIPLICATION_MATRIXBLOCKMULDATA_H
#define MATRIXMULTIPLICATION_MATRIXBLOCKMULDATA_H


#include "MatrixBlockData.h"

template <class Type>
class MatrixBlockMulData{
public:

    MatrixBlockMulData(const std::shared_ptr<MatrixBlockData<Type>> &matrixA,
                       const std::shared_ptr<MatrixBlockData<Type>> &matrixB,
                       const std::shared_ptr<MatrixBlockData<Type>> &matrixC) :
            matrixA(matrixA), matrixB(matrixB), matrixC(matrixC) {}

    const std::shared_ptr<MatrixBlockData<Type>> &getMatrixA() const {
        return matrixA;
    }
    const std::shared_ptr<MatrixBlockData<Type>> &getMatrixB() const {
        return matrixB;
    }

    const std::shared_ptr<MatrixBlockData<Type>> &getMatrixC() const {
        return matrixC;
    }

private:
    std::shared_ptr<MatrixBlockData<Type>> matrixA;
    std::shared_ptr<MatrixBlockData<Type>> matrixB;
    std::shared_ptr<MatrixBlockData<Type>> matrixC;
};


#endif //MATRIXMULTIPLICATION_MATRIXBLOCKMULDATA_H

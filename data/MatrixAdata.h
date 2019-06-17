//
// Created by henok on 6/17/19.
//

#ifndef MATRIXMULTIPLICATION_MATRIXADATA_H
#define MATRIXMULTIPLICATION_MATRIXADATA_H


#include "hedgehog.h"
#include "./MatrixRequestData.h"
template<class Type>
class MatrixAdata {
public:
    MatrixAdata(const std::shared_ptr<MatrixRequestData> &request,
                    Type &matrixData,
                    size_t matrixWidth,
                    size_t matrixHeight,
                    size_t leadingDimension) :
            request(request), matrixData(matrixData), matrixWidth(matrixWidth), matrixHeight(matrixHeight), leadingDimension(leadingDimension) {}

    const std::shared_ptr<MatrixRequestData> &getRequest() const {
        return request;
    }
    Type &getMatrixData()  {
        return matrixData;
    }
    size_t getMatrixWidth() const {
        return matrixWidth;
    }
    size_t getMatrixHeight() const {
        return matrixHeight;
    }

    size_t getLeadingDimension() const {
        return leadingDimension;
    }

private:
    std::shared_ptr<MatrixRequestData> request;
    Type matrixData;
    size_t matrixWidth;
    size_t matrixHeight;
    size_t leadingDimension;
};


#endif //MATRIXMULTIPLICATION_MATRIXADATA_H

//
// Created by henok on 6/18/19.
//

#ifndef MATRIXMULTIPLICATION_PRODUCTTASK_H
#define MATRIXMULTIPLICATION_PRODUCTTASK_H

#include "hedgehog.h"
#include "../data/MatrixBlockData.h"
#include "../data/MatrixBlockMulData.h"

class ProductTask : public AbstractTask<MatrixBlockData<int *>,MatrixBlockMulData>{
public:
    ProductTask(const std::string_view &name, size_t numberThreads):AbstractTask(name, numberThreads){}
    void execute(std::shared_ptr<MatrixBlockMulData> data){
        auto matAData = data->getMatrixA();
        auto matBData = data->getMatrixB();

        int *matrixA = matAData->getMatrixData();
        int *matrixB = matBData->getMatrixData();


        size_t width = matAData->getMatrixWidth();
        size_t height = matAData->getMatrixHeight();

        int *result = new int[width * height];

        for (size_t i = 0; i < matAData->getMatrixWidth() * matAData->getMatrixHeight(); i++) {
            result[i] = matrixA[i] * matrixB[i];
        }

        delete []matrixA;
        matrixA = nullptr;

        delete []matrixB;
        matrixB = nullptr;

        auto matRequest = matAData->getRequest();

        std::shared_ptr<MatrixRequestData>
                matReq(new MatrixRequestData(matRequest->getRow(), matRequest->getCol(), 'C'));

        addResult(std::make_shared<MatrixBlockData<int *>>(matReq, result, width, height, width));
    }

    std::shared_ptr<AbstractTask<MatrixBlockData<int *>,MatrixBlockMulData>> copy() override {
        return std::make_shared<ProductTask>(this->name(),this->numberThreads());
    }
};


#endif //MATRIXMULTIPLICATION_PRODUCTTASK_H

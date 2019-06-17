//
// Created by henok on 6/17/19.
//

#ifndef MATRIXMULTIPLICATION_GENMATRIXBTASK_H
#define MATRIXMULTIPLICATION_GENMATRIXBTASK_H


#include <hedgehog.h>
#include "../data/MatrixRequestData.h"
#include "../data/MatrixBdata.h"

class GenMatrixBtask: public AbstractTask<MatrixBdata<int *>,MatrixRequestData>{
public:

    GenMatrixBtask(const std::string_view &name, size_t numberThreads, size_t blockSize, size_t fullMatrixWidth, size_t fullMatrixHeight) : AbstractTask(name,numberThreads), blockSize(blockSize), fullMatrixHeight(fullMatrixHeight), fullMatrixWidth(fullMatrixWidth) {

        numBlocksRows = (size_t) ceil((double) fullMatrixHeight / (double) blockSize);
        numBlocksCols = (size_t) ceil((double) fullMatrixWidth / (double) blockSize);
    }

    void execute(std::shared_ptr<MatrixRequestData> data) {
        if(data->getType()=='B'){
            size_t row = data->getRow();
            size_t col = data->getCol();

            size_t matrixWidth;
            size_t matrixHeight;

            if (col == numBlocksCols - 1 && fullMatrixWidth % blockSize != 0)
                matrixWidth = fullMatrixWidth % blockSize;
            else
                matrixWidth = blockSize;

            if (row == numBlocksRows - 1 && fullMatrixHeight % blockSize != 0)
                matrixHeight = fullMatrixHeight % blockSize;
            else
                matrixHeight = blockSize;

            // Allocate matrix Memory
            int *matrixData = new int[matrixHeight*matrixWidth];
            // Initialize with a simple value
            for (int i = 0; i < matrixWidth * matrixHeight; i++)
                matrixData[i] = 2;

            std::shared_ptr<MatrixBdata<int *>> matrixBdata = std::make_shared<MatrixBdata<int *>>(data, matrixData, matrixWidth, matrixHeight, matrixWidth);
            addResult(matrixBdata);
        }
    }

    size_t getNumBlocksRows() const {
        return numBlocksRows;
    }
    size_t getNumBlocksCols() const {
        return numBlocksCols;
    }

    std::shared_ptr<AbstractTask<MatrixBdata<int *>,MatrixRequestData>> copy() override{
        return std::make_shared<GenMatrixBtask>(this->name(),this->numberThreads(), this->blockSize, this->fullMatrixWidth, this->fullMatrixHeight);
    }
private:
    size_t blockSize;
    size_t fullMatrixWidth;
    size_t fullMatrixHeight;
    size_t numBlocksRows;
    size_t numBlocksCols;

};


#endif //MATRIXMULTIPLICATION_GENMATRIXBTASK_H

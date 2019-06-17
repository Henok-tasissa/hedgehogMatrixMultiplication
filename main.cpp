#include <iostream>
#include "hedgehog.h"
#include "./data/MatrixRequestData.h"
#include "./data/MatrixBlockData.h"
#include "./task/GenMatrixTask.h"
int main() {
    size_t width = 1024;
    size_t height = 1024;
    size_t blockSize = 256;
    size_t numThreads = 4;

    std::shared_ptr<GenMatrixTask> genMatrixTask = std::make_shared<GenMatrixTask>("GenMatrixTask",numThreads,blockSize,width,height);

    size_t numBlocksCols = genMatrixTask->getNumBlocksCols();
    size_t numBlocksRows = genMatrixTask->getNumBlocksRows();

    auto myGraph = std::make_shared<Graph<MatrixBlockData<int *>,MatrixRequestData>>();

    myGraph->input(genMatrixTask);
    myGraph->output(genMatrixTask);
    myGraph->executeGraph();

    for(size_t row = 0; row<numBlocksRows;row++){
        for(size_t col = 0; col<numBlocksCols;col++){
            std::shared_ptr<MatrixRequestData> matrixA = std::make_shared<MatrixRequestData>(row,col,'A');
            std::shared_ptr<MatrixRequestData> matrixB = std::make_shared<MatrixRequestData>(row,col,'B');

            myGraph->pushData(matrixA);
            myGraph->pushData(matrixB);
        }
    }
    myGraph->finishPushingData();
    int count = 0;
    while(std::shared_ptr<MatrixBlockData<int *>> graphOutput = myGraph->getBlockingResult()){
        count+=1;
        std::cout<<graphOutput->getMatrixWidth()<<std::endl;
    }
    std::cout<<count<<std::endl;
    myGraph->waitForTermination();

    return 0;
}

#include <iostream>
#include "hedgehog.h"
#include "./data/MatrixRequestData.h"
#include "./data/MatrixBlockData.h"
#include "./task/GenMatrixAtask.h"
#include "./task/GenMatrixBtask.h"
#include "state/MatrixState.h"

int main() {
    size_t width = 1024;
    size_t height = 1024;
    size_t blockSize = 256;
    size_t numThreads = 5;

    std::shared_ptr<GenMatrixAtask> genMatrixAtask = std::make_shared<GenMatrixAtask>("GenMatrixAtask",numThreads,blockSize,width,height);
    std::shared_ptr<GenMatrixBtask> genMatrixBtask = std::make_shared<GenMatrixBtask>("GenMatrixBtask",numThreads,blockSize,width,height);

    size_t numMatrixAblocksCols = genMatrixAtask->getNumBlocksCols();
    size_t numMatrixAblocksRows = genMatrixAtask->getNumBlocksRows();


    size_t numMatrixBblocksCols = genMatrixBtask->getNumBlocksCols();
    size_t numMatrixBblocksRows = genMatrixBtask->getNumBlocksRows();

    auto myGraph = std::make_shared<Graph<MatrixBlockMulData<int *>,MatrixRequestData>>();

    std::shared_ptr<MatrixState> matrixState = std::make_shared<MatrixState>();
    std::shared_ptr<DefaultStateManager<MatrixBlockMulData<int *>,MatrixAdata<int *>,MatrixBdata<int *>>> stateManager =
            std::make_shared<DefaultStateManager<MatrixBlockMulData<int *>,MatrixAdata<int *>,MatrixBdata<int *>>>(matrixState);

    myGraph->input(genMatrixAtask);
    myGraph->input(genMatrixBtask);
    myGraph->addEdge(genMatrixAtask,stateManager);
    myGraph->addEdge(genMatrixBtask,stateManager);
    myGraph->output(stateManager);
    myGraph->executeGraph();

    for(size_t row = 0; row<numMatrixAblocksRows;row++){
        for(size_t col = 0; col<numMatrixAblocksCols;col++){
            std::shared_ptr<MatrixRequestData> matrixA = std::make_shared<MatrixRequestData>(row,col,'A');
            myGraph->pushData(matrixA);
        }
    }
    for(size_t row = 0; row<numMatrixBblocksRows;row++){
        for(size_t col = 0; col<numMatrixBblocksCols;col++){
            std::shared_ptr<MatrixRequestData> matrixB = std::make_shared<MatrixRequestData>(row,col,'B');
            myGraph->pushData(matrixB);
        }
    }

    myGraph->finishPushingData();
    int count = 0;
    while(std::shared_ptr<MatrixBlockMulData<int *>> graphOutput = myGraph->getBlockingResult()){
        count+=1;
    }
    std::cout<<count<<std::endl;
    myGraph->waitForTermination();

    return 0;
}

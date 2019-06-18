#include <iostream>
#include "hedgehog.h"
#include "./data/MatrixRequestData.h"
#include "./data/MatrixAdata.h"
#include "./data/MatrixBdata.h"
#include "./task/GenMatrixAtask.h"
#include "./task/GenMatrixBtask.h"
#include "state/MatrixState.h"
#include "task/ProductTask.h"

int main() {
    size_t width = 1024;
    size_t height = 1024;
    size_t blockSize = 256;
    size_t numThreads = 5;

    std::shared_ptr<GenMatrixAtask> genMatrixAtask = std::make_shared<GenMatrixAtask>("GenMatrixAtask",numThreads,blockSize,width,height);
    std::shared_ptr<GenMatrixBtask> genMatrixBtask = std::make_shared<GenMatrixBtask>("GenMatrixBtask",numThreads,blockSize,width,height);

    size_t numBlockCols = genMatrixAtask->getNumBlocksCols();
    size_t numBlockRows = genMatrixAtask->getNumBlocksRows();


    auto myGraph = std::make_shared<Graph<MatrixBlockData<int *>,MatrixRequestData>>();

    auto matrixState = std::make_shared<MatrixState<int *>>(numBlockCols, numBlockRows);
    auto productTask = std::make_shared<ProductTask>("Product Task", numThreads);

    std::shared_ptr<DefaultStateManager<MatrixBlockMulData,MatrixAdata<int *>,MatrixBdata<int *>>> stateManager =
            std::make_shared<DefaultStateManager<MatrixBlockMulData,MatrixAdata<int *>,MatrixBdata<int *>>>(matrixState);
    myGraph->input(genMatrixAtask);
    myGraph->input(genMatrixBtask);

    myGraph->addEdge(genMatrixAtask,stateManager);
    myGraph->addEdge(genMatrixBtask,stateManager);
    myGraph->addEdge(stateManager,productTask);
    myGraph->output(productTask);
    myGraph->executeGraph();

    for(size_t row = 0; row<numBlockRows;row++){
        for(size_t col = 0; col<numBlockCols;col++){
            std::shared_ptr<MatrixRequestData> matrixA = std::make_shared<MatrixRequestData>(row,col,'A');
            myGraph->pushData(matrixA);
        }
    }
    for(size_t row = 0; row<numBlockRows;row++){
        for(size_t col = 0; col<numBlockCols;col++){
            std::shared_ptr<MatrixRequestData> matrixB = std::make_shared<MatrixRequestData>(row,col,'B');
            myGraph->pushData(matrixB);
        }
    }

    myGraph->finishPushingData();
    while(std::shared_ptr<MatrixBlockData<int *>> graphOutput = myGraph->getBlockingResult()){
        for (size_t i = 0; i < graphOutput->getMatrixHeight()*graphOutput->getMatrixWidth(); ++i) {
            std::cout<<graphOutput->getMatrixData()[i]<<", ";
        }
    }
    myGraph->waitForTermination();

    myGraph->createDotFile("matrixProduct.dot",ColorScheme::WAIT,StructureOptions::ALL);
    return 0;
}

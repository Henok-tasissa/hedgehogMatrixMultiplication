//
// Created by hnt9 on 6/17/19.
//

#ifndef MATRIXMULTIPLICATION_MATRIXSTATE_H
#define MATRIXMULTIPLICATION_MATRIXSTATE_H

#include "hedgehog.h"
#include "./StateContainer.h"
#include "../data/MatrixBlockData.h"
#include "../data/MatrixAdata.h"
#include "../data/MatrixBdata.h"
#include "../data/MatrixBlockMulData.h"
#include "StateContainer.h"

class MatrixState: public AbstractState<MatrixBlockMulData<int *>,MatrixAdata<int *>,MatrixBdata<int *>> {
public:
    void execute(std::shared_ptr<MatrixAdata<int *>> matrixAdata) override{
        std::cout<<"MatrixAdata"<<std::endl;
    }

    void execute(std::shared_ptr<MatrixBdata<int *>> matrixBdata) override{
        std::cout<<"MatrixBdata"<<std::endl;
    }


private:

};


#endif //MATRIXMULTIPLICATION_MATRIXSTATE_H

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
template <class T>
class MatrixState: public AbstractState<MatrixBlockMulData,MatrixAdata<int *>,MatrixBdata<int *>> {
public:
    MatrixState(size_t blockWidth, size_t blockHeight){
        this->matrixAState = new StateContainer<std::shared_ptr<MatrixAdata<T>>>(blockHeight,blockWidth, nullptr);
        this->matrixBState = new StateContainer<std::shared_ptr<MatrixBdata<T>>>(blockHeight,blockWidth, nullptr);
    }
    void execute(std::shared_ptr<MatrixAdata<int *>> data) override{
        std::shared_ptr<MatrixRequestData> request = data->getRequest();

        this->matrixAState->set(request->getRow(),request->getCol(),data);

        if(this->matrixBState->has(request->getRow(),request->getCol())){
            auto matrixBdata = this->matrixBState->get(request->getRow(),request->getCol());
            auto matrixMulData = std::make_shared<MatrixBlockMulData>(data,matrixBdata);
            this->push(matrixMulData);
          }
    }

    void execute(std::shared_ptr<MatrixBdata<int *>> data) override{
        std::shared_ptr<MatrixRequestData> request = data->getRequest();
        this->matrixBState->set(request->getRow(),request->getCol(),data);
        if(this->matrixAState->has(request->getRow(),request->getCol())){
            auto matrixAdata = this->matrixAState->get(request->getRow(),request->getCol());
            auto matrixMulData = std::make_shared<MatrixBlockMulData>(matrixAdata,data);
            this->push(matrixMulData);
        }
    }

private:
    StateContainer<std::shared_ptr<MatrixAdata<T>>> *matrixAState;
    StateContainer<std::shared_ptr<MatrixBdata<T>>> *matrixBState;

};


#endif //MATRIXMULTIPLICATION_MATRIXSTATE_H

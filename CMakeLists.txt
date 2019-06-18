cmake_minimum_required(VERSION 3.14)
project(MatrixMultiplication)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")
find_package(Hedgehog REQUIRED)

add_executable(MatrixMultiplication main.cpp task/GenMatrixTask.h data/MatrixRequestData.h data/MatrixBlockData.h state/StateContainer.h state/MatrixState.h data/MatrixAdata.h data/MatrixBdata.h task/GenMatrixAtask.h task/GenMatrixBtask.h data/MatrixBlockMulData.h task/ProductTask.h)

target_include_directories(MatrixMultiplication PUBLIC ${Hedgehog_INCLUDE_DIR})
target_link_libraries(MatrixMultiplication ${Hedgehog_LIBRARIES})
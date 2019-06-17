cmake_minimum_required(VERSION 3.14)
project(MatrixMultiplication)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules")
find_package(Hedgehog REQUIRED)

add_executable(MatrixMultiplication main.cpp task/GenMatrixTask.h data/MatrixRequestData.h data/MatrixBlockData.h data/StateContainer.h data/MatrixState.h)

target_include_directories(MatrixMultiplication PUBLIC ${Hedgehog_INCLUDE_DIR})
target_link_libraries(MatrixMultiplication ${Hedgehog_LIBRARIES})
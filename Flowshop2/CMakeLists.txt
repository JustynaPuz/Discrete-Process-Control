cmake_minimum_required(VERSION 3.27)
project(Flowshop2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Flowshop2 main.cpp
        src/Problem.cpp
        inc/TestAlgorithm.h
        src/TestAlgorithm.cpp)

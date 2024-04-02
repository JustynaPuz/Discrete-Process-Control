cmake_minimum_required(VERSION 3.27)
project(Single)

set(CMAKE_CXX_STANDARD 17)

add_executable(Single main.cpp
        inc/Problem.h
        inc/Task.h
        inc/Solution.h
        src/Problem.cpp
        src/Solution.cpp
        inc/TestAlgorithm.h
        src/TestAlgorithm.cpp)

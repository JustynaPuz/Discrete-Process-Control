cmake_minimum_required(VERSION 3.27)
project(SingleMachineProblem_)

set(CMAKE_CXX_STANDARD 17)

set(Headers inc/Problem.h inc/Solution.h inc/Task.h inc/TestAlgorithm.h)

add_executable(SingleMachineProblem ${PROJECT_SOURCE_DIR}/ main.cpp src/Problem.cpp src/Solution.cpp src/Task.cpp src/TestTime.cpp)



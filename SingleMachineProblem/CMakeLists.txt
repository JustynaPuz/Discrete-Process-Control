cmake_minimum_required(VERSION 3.27)
project(SingleMachineProblem_)

set(CMAKE_CXX_STANDARD 17)

add_executable(SingleMachineProblem main.cpp src/Problem.cpp src/Task.cpp src/Solution.cpp resources/instance.txt)



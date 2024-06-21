//
// Created by Justyna on 11.03.2024.
//

#ifndef SINGLEMACHINEPROBLEM_PROBLEM_H
#define SINGLEMACHINEPROBLEM_PROBLEM_H

#include <vector>
#include "Task.h"
#include "Solution.h"


class Problem {
    int numberOfTasks = 0;
    int numberOfMachines = 0;
    std::vector<Task> tasks;
    std::vector<std::vector<Task>> allPermutation;

public:

    Problem(int number, int machines, std::vector<Task> tasks) {
        numberOfTasks = number;
        numberOfMachines = machines;
        tasks.reserve(number);
        this->tasks.swap(tasks);
    }

    Problem() = default;

    std::vector<Task> sortTime(std::vector<Task> permutation);

    std::vector<Task> sortJohnsonTime(std::vector<Task> permutation, bool isAscending);

    void generateAllPermutation();

    int calculateTime(std::vector<Task> permutation);

    int completeOverview();

    Solution NEH();

    Solution Johnson();

    Solution FNeh();

    Solution TabuSearch(std::vector<Task> initialSolution, int numOfIterations, int tabuListSize);

    Solution thresholdAccepting(int numOfIterations, double initialThreshold, double decayRate);

    std::vector<Task> generateNeighbor(const std::vector<Task> &solution);
};
#endif //SINGLEMACHINEPROBLEM_PROBLEM_H

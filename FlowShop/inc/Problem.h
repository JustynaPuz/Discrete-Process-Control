//
// Created by Justyna on 11.03.2024.
//

#ifndef SINGLEMACHINEPROBLEM_PROBLEM_H
#define SINGLEMACHINEPROBLEM_PROBLEM_H

#include <vector>
#include "Task.h"


class Problem {
    int numberOfTasks =0;
    int numberOfMachines=0;
    std::vector<Task> tasks;
    std::vector<std::vector<Task>> allPermutation;

public:

    Problem(int number, std::vector<Task> tasks ) {
        numberOfTasks = number;
        tasks.reserve(number);
        this->tasks.swap(tasks);
    }

    Problem() = default;
    void sortR();
    void sortQ();
    void generateAllPermutation();
    double calculateTime(std::vector<Task> permutation);

};

#endif //SINGLEMACHINEPROBLEM_PROBLEM_H

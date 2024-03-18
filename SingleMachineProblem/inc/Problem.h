//
// Created by Justyna on 11.03.2024.
//

#ifndef SINGLEMACHINEPROBLEM_PROBLEM_H
#define SINGLEMACHINEPROBLEM_PROBLEM_H

#include <vector>
#include "Task.h"
#include "Solution.h"


class Problem {
    int numberOfTasks =0;
    std::vector<Task> tasks;
    // std::vector<std::vector<Task>> allPermutation;


public:

    Problem(int number, std::vector<Task> tasks ) {
        numberOfTasks = number;
        tasks.reserve(number);
        this->tasks.swap(tasks);
    }

    Problem() = default;
    Solution generatePermutation();
    double calculateTime(std::vector<Task>);
    Solution permutationSortR();
    Solution permutationSortQ();
    Solution schrage();

};

#endif //SINGLEMACHINEPROBLEM_PROBLEM_H

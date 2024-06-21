//
// Created by Justyna on 11.03.2024.
//

#ifndef SINGLEMACHINEPROBLEM_SOLUTION_H
#define SINGLEMACHINEPROBLEM_SOLUTION_H

#include <vector>

class Solution {
    double criterion;
    std::vector<int> ranked;

    Solution(double criterion, std::vector<int> ranked) {
        this->criterion = criterion;
        this->ranked= ranked;

    }

};


#endif //SINGLEMACHINEPROBLEM_SOLUTION_H

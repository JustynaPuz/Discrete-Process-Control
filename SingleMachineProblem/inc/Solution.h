//
// Created by Justyna on 11.03.2024.
//

#ifndef SINGLEMACHINEPROBLEM_SOLUTION_H
#define SINGLEMACHINEPROBLEM_SOLUTION_H

#include <vector>
#include <string>
#include <iostream>
#include "Task.h"

class Solution {
    std::string criterion;
    std::vector<Task> ranked;
    double timeOfBestPermutation;

public:
    Solution(std::string criterion, std::vector<Task> ranked, double timeOfBestPermutation) {
        this->criterion = criterion;
        this->ranked = ranked;
        this->timeOfBestPermutation = timeOfBestPermutation;
    }

    friend std::ostream& operator<<(std::ostream& os, const Solution& solution) {
        os << "Kryterium: " << solution.criterion << ", czas: " << solution.timeOfBestPermutation;
        return os;
    }

     std::string getCriterium() {
        return this->criterion;
    }

    double getTimeOfBestPermutation() {
        return this->timeOfBestPermutation;
    }
};


#endif //SINGLEMACHINEPROBLEM_SOLUTION_H

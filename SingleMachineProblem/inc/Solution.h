//
// Created by Justyna on 02.04.2024.
//

#ifndef SINGLE_SOLUTION_H
#define SINGLE_SOLUTION_H

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


#endif //SINGLE_SOLUTION_H

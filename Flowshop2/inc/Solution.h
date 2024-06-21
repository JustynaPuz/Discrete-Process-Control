//
// Created by Justyna on 11.03.2024.
//

#ifndef SINGLEMACHINEPROBLEM_SOLUTION_H
#define SINGLEMACHINEPROBLEM_SOLUTION_H

#include <vector>
#include <string>
#include <iostream>

class Solution {
    std::string criterion;
    int bestTime;
    std::vector<Task> orderOfTasks;

public:
    Solution(std::string criterion, int time) {
        this->criterion = criterion;
        this->bestTime = time;
    }

    Solution(std::string criterion, int time, std::vector<Task> orderOfTasks) {
        this->criterion = criterion;
        this->bestTime = time;
        this->orderOfTasks = orderOfTasks;
    }

    std::vector<Task> getTasks(){
        return orderOfTasks;
    }

    friend std::ostream& operator<<(std::ostream& os, const Solution& solution) {

        os << "Kryterium: " << solution.criterion << ", czas na maszynach: " << solution.bestTime;
        return os;
    }
};


#endif //SINGLEMACHINEPROBLEM_SOLUTION_H

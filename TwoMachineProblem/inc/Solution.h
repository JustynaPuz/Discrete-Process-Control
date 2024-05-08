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
    std::vector<Task> rankedFirstMachine;
    std::vector<Task> rankedSecondMachine;
    double timeOfBestPermutationFirst;
    double timeOfBestPermutationSecond;

public:
    Solution(std::string criterion, std::vector<Task> rankedFirstMachine, std::vector<Task> rankedSecondMachine, double timeOfBestPermutationFirst,double timeOfBestPermutationSecond) {
        this->criterion = criterion;
        this->rankedFirstMachine = rankedFirstMachine;
        this->rankedSecondMachine = rankedSecondMachine;
        this->timeOfBestPermutationFirst = timeOfBestPermutationFirst;
        this->timeOfBestPermutationSecond = timeOfBestPermutationSecond;
    }

    friend std::ostream& operator<<(std::ostream& os, const Solution& solution) {

        os << "Kryterium: " << solution.criterion << ", czas pierwszy: " << solution.timeOfBestPermutationFirst ;
        os <<  " czas drugi: " << solution.timeOfBestPermutationSecond ;
        return os;
    }

    std::string getCriterium() {
        return this->criterion;
    }

    double getTimeOfBestPermutationFirst() {
        return this->timeOfBestPermutationFirst;
    }

    double getTimeOfBestPermutationSecond() {
        return this->timeOfBestPermutationSecond;
    }
    void setTimeOfBestPermutationFirst(double time) {timeOfBestPermutationFirst = time;}
    void setTimeOfBestPermutationSecond(double time) {timeOfBestPermutationSecond = time;}
    void setRankedFirstMachine(std::vector<Task> task) {rankedFirstMachine = task;}
    void setRankedSecondMachine(std::vector<Task> task) {rankedSecondMachine = task;}
};


#endif //SINGLE_SOLUTION_H

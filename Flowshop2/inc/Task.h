//
// Created by Justyna on 11.03.2024.
//

#ifndef SINGLEMACHINEPROBLEM_TASK_H
#define SINGLEMACHINEPROBLEM_TASK_H


class Task {
    std::vector<int> p_j;
    int index;
    int sumOfTime;

public:
    Task(int numberOfMachines,int index) {
        p_j.reserve(numberOfMachines);
        this->index = index;
        this->sumOfTime = 0;
   }

    int getIndex() {return index;}
    void addPJ(int time) { p_j.push_back(time); sumOfTime += time;}
    std::vector<int> getPJ() { return p_j;}
    int getSpecificPJ(int index) {return p_j.at(index);}
    int getTime() {return sumOfTime;}

};


#endif //SINGLEMACHINEPROBLEM_TASK_H

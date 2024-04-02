
#include "../inc/Problem.h"
#include<algorithm>
#include <queue>
#include <iostream>
#include <functional>

bool sortRKey ( Task task1, Task task2 ){
    return (task1.getR() < task2.getR());
}

bool sortQKey ( Task task1, Task task2 ){
    return (task1.getQ() < task2.getQ());
}

std::vector<Task> sortR(std::vector<Task> permutation) {
    std::sort(permutation.begin(), permutation.end(), sortRKey);
    return permutation;
}

std::vector<Task> sortQ(std::vector<Task> permutation) {
    std::sort(permutation.begin(), permutation.end(), sortQKey);
    return permutation;
}

struct compareQ {
    bool operator()( Task&  task1, Task& task2){
        return (task1.getQ() < task2.getQ());
    }
};

double Problem::calculateTime(std::vector<Task> permutation) {
    double endOfProcessTime = 0, endOfTasksTime = 0;

    for(int i=0; i < numberOfTasks; i++){
        if (endOfTasksTime >= permutation[i].getR()) {
            endOfTasksTime += permutation[i].getP();

        }
        else {
            endOfTasksTime += permutation[i].getR() - endOfTasksTime + permutation[i].getP();
        }

        if(endOfProcessTime < endOfTasksTime + permutation[i].getQ()){
            endOfProcessTime = endOfTasksTime + permutation[i].getQ();
        }
    }
    return endOfProcessTime;
}

Solution Problem::permutationSortR() {
    std::vector<Task> permutation = this->tasks;
    permutation = sortR(permutation);

    double currentTime = 0;
    currentTime = calculateTime(permutation);

    Solution solution("Sort R", permutation, currentTime);
    return  solution;
}

Solution Problem::permutationSortQ() {
    std::vector<Task> permutation = this->tasks;
    permutation = sortQ(permutation);

    double currentTime = 0;
    currentTime = calculateTime(permutation);

    Solution solution("Sort Q", permutation, currentTime);
    return  solution;
}

Solution Problem::generatePermutation() {

    double currentTime = 0, bestTime = INT_MAX;

    std::vector<Task> bestPermutation;
    std::vector<int> indexes(tasks.size());
    for (int i =0; i < tasks.size(); i++) {
        indexes[i] = i;
    }

    do{
        std::vector<Task> currentPermutation;
        for(int index : indexes) {
            currentPermutation.push_back(tasks[index]);
        }
        currentTime = calculateTime(currentPermutation);
        if (currentTime < bestTime){

            bestTime = currentTime;
            bestPermutation = currentPermutation;
        }

    }while(std::next_permutation(indexes.begin(), indexes.end()));

    Solution solution("Complete review", bestPermutation, calculateTime(bestPermutation));
    return  solution;
}

void transferConditionally(std::priority_queue<Task, std::vector<Task>, compareQ>& tasksByQ,
                           std::priority_queue<Task, std::vector<Task>, compareQ>& availableTasks, int time) {
    std::vector<Task> temporary;

    while(!tasksByQ.empty()){
        Task task = tasksByQ.top();
        tasksByQ.pop();
        if( task.getR() <= time) {
            availableTasks.push(task);
        }else{
            temporary.push_back(task);
        }

    }

    for(Task task : temporary) {
        tasksByQ.push(task);
    }

}
Solution Problem::schrage() {
    std::vector<Task> permutation = this->tasks;
    std::priority_queue<Task, std::vector<Task>, compareQ>  tasksByQ ;
    std::priority_queue<Task, std::vector<Task>, compareQ>  availableTasks;
    std::vector<Task> bestPermutation;
    permutation = sortR(permutation);
    int time =0;

    auto condition = [time](const Task& task) {return task.getR() <= time;};

    for(Task task : permutation){
        tasksByQ.push(task);
    }

    while(!tasksByQ.empty() || !availableTasks.empty()) {
        if(!tasksByQ.empty() && permutation[0].getR() <= time ) {
            transferConditionally(tasksByQ, availableTasks, time);
        }

        if(availableTasks.empty()) {
            time = permutation[0].getR();
        } else {
            Task task = availableTasks.top();
            availableTasks.pop();
            bestPermutation.push_back(task);
            permutation.erase(std::remove_if(permutation.begin(), permutation.end(),[&task](Task x) {return x.getIndex() == task.getIndex();}),permutation.end());

            time += task.getP();
        }
    }
    time = calculateTime(bestPermutation);

    Solution solution("Schrage", permutation, calculateTime(bestPermutation));
    return  solution;
}

Solution Problem::betterSchrage() {
    std::vector<Task> permutation = this->tasks;
    std::priority_queue<Task, std::vector<Task>, compareQ>  tasksByQ ;
    std::priority_queue<Task, std::vector<Task>, compareQ>  availableTasks;
    std::vector<Task> bestPermutation;
    permutation = sortR(permutation);
    int time = 0;
    int endTime = 0;

    auto condition = [time](const Task& task) {return task.getR() <= time;};

    for(Task task : permutation){
        tasksByQ.push(task);
    }

    while(!tasksByQ.empty() || !availableTasks.empty()) {
        if (!tasksByQ.empty() && permutation[0].getR() <= time) {
            transferConditionally(tasksByQ, availableTasks, time);
        }
        if (availableTasks.empty()) {
            time += permutation[0].getR();
        } else {
            Task task = availableTasks.top();
            availableTasks.pop();
            time++;
            task.setP(task.getP() - 1);
            if (task.getP() > 0) {
                transferConditionally(tasksByQ, availableTasks, time);
                if (availableTasks.top().getQ() > task.getQ()) {
                    availableTasks.push(task);
                    task = availableTasks.top();
                    availableTasks.pop();
                }
            } else {
                if(endTime < time + task.getQ()) {
                    endTime = time + task.getQ();
                }
                bestPermutation.push_back(task);
                if(!availableTasks.empty()) {
                    task = availableTasks.top();
                    availableTasks.pop();
                }
            }
            if(!availableTasks.empty()) {
                availableTasks.push(task);
            }

        }
    }
    Solution solution("BetterSchrage", permutation, endTime);
    return  solution;
}

Solution Problem::puzAndOwczarekMethod() {
    std::vector<Task> permutation = this->tasks;
    std::vector<Task> bestPerm;
    std::vector<Task> tmpPerm;
    int time = 0;
    int bestTime = 0;
    int endTime = 0;

    while(!permutation.empty()){

        Task task = permutation.back();
        tmpPerm.push_back(task);

        for(int i = 0; i < tmpPerm.size() - 1; i++){

            bestTime = calculateTime(tmpPerm);
            bestPerm=tmpPerm;
            if(tmpPerm.size() > 1){
                std::swap(tmpPerm[tmpPerm.size() - 1 - i], tmpPerm[tmpPerm.size() - 2 - i]);}
            time = calculateTime(tmpPerm);

            if(bestTime < time){
                bestPerm = tmpPerm;
            }

        }
        permutation.pop_back();
    }

    time = calculateTime(bestPerm);

    Solution solution("Custom Algorithm", bestPerm, time);
    return solution;
}

#include "../inc/Problem.h"
#include<algorithm>


bool sortRKey ( Task task1, Task task2 ){
    return (task1.getR() < task2.getR());
}
bool sortQKey ( Task task1, Task task2 ){
    return (task1.getQ() < task2.getQ());
}


void Problem::sortR() {
    std::sort(tasks.begin(), tasks.end(), sortRKey);
}

void Problem::sortQ() {
    std::sort(tasks.begin(), tasks.end(), sortQKey);
}

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

void Problem::generatePermutation() {

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

    this->bestPermutation = bestPermutation;
    this->timeOfBestPermutation = bestTime;

}





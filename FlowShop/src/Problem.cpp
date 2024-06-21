
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

void Problem::generateAllPermutation() {

    std::vector<int> indexes(tasks.size());
    for (int i =0; i < tasks.size(); i++) {
        indexes[i] = i;
    }

    do{
        std::vector<Task> currentPermutation;
        for(int index : indexes) {
            currentPermutation.push_back(tasks[index]);
        }
        allPermutation.push_back(currentPermutation);

    }while(std::next_permutation(indexes.begin(), indexes.end()));

}


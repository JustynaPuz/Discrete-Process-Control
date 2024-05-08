
#include "../inc/Problem.h"
#include<algorithm>
#include <queue>
#include <iostream>
#include <functional>
#include <cfloat>
/*

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
                std::swap(tmpPerm[tmpPerm.size() - 1 - i], tmpPerm[tmpPerm.size() - 2 - i]);
            }
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
}*/
Solution Problem::LSA() {

    std::vector<Task> firstMachine;
    std::vector<Task> secondMachine;
    std::vector<Task> allTasks = this->tasks;
    double firstTime;
    double secondTime;

    firstMachine.push_back(allTasks[0]);
    secondMachine.push_back(allTasks[1]);
    firstTime = allTasks[0].getP();
    secondTime = allTasks[1].getP();

    for(int i =2; i < allTasks.size(); i++) {
        if(firstTime <= secondTime) {
            firstMachine.push_back(allTasks[i]);
            firstTime += allTasks[i].getP();
        }else {
            secondMachine.push_back(allTasks[i]);
            secondTime += allTasks[i].getP();
        }
    }

    Solution solution("LSA", firstMachine, secondMachine, firstTime,secondTime);
    return solution;
}

bool sortPKey ( Task task1, Task task2 ){
    return (task1.getP() < task2.getP());
}

std::vector<Task> sortP(std::vector<Task> permutation) {
    std::sort(permutation.begin(), permutation.end(), sortPKey);
    return permutation;
}

Solution Problem::LPT() {

    std::vector<Task> firstMachine;
    std::vector<Task> secondMachine;
    std::vector<Task> allTasks = this->tasks;
    allTasks = sortP(allTasks);

    double firstTime;
    double secondTime;

    firstMachine.push_back(allTasks[0]);
    secondMachine.push_back(allTasks[1]);
    firstTime = allTasks[0].getP();
    secondTime = allTasks[1].getP();

    for(int i =2; i < allTasks.size(); i++) {
        if(firstTime <= secondTime) {
            firstMachine.push_back(allTasks[i]);
            firstTime += allTasks[i].getP();
        }else {
            secondMachine.push_back(allTasks[i]);
            secondTime += allTasks[i].getP();
        }
    }

    Solution solution("LPT", firstMachine, secondMachine, firstTime,secondTime);
    return solution;
}

// Function to generate all binary strings
void Problem::generateAllBinaryStrings(int n, std::vector<int> arr, int i)
{

    if (i == n) {
        this->allCombinations.push_back(arr);
        return;
    }
    arr[i] = 0;
    generateAllBinaryStrings(n, arr, i + 1);

    arr[i] = 1;
    generateAllBinaryStrings(n, arr, i + 1);
}

Solution Problem::CompleteOverview()  {

    std::vector<Task> firstMachine;
    std::vector<Task> secondMachine;
    std::vector<Task> allTasks = this->tasks;
    std::vector<int> tmp;
    tmp.resize(numberOfTasks);
    //allTasks = sortP(allTasks);

    double firstTime =0;
    double secondTime =0;
    double BestFirstTime = DBL_MAX;
    double longerTime;

    generateAllBinaryStrings(this->numberOfTasks, tmp, 0);
    Solution solution("CompleteOverview", firstMachine, secondMachine, BestFirstTime, 0);
    int counter =0;
    for(int i = 0; i < this->allCombinations.size()/2; i++){
        counter =0;
        for(int j : this->allCombinations[i]){
            if(j==0) {
                firstTime += allTasks[counter].getP();
                firstMachine.push_back(allTasks[counter]);
            }
            else {
                secondTime += allTasks[counter].getP();
                secondMachine.push_back(allTasks[counter]);
            }
            counter++;
        }
        longerTime = (firstTime > secondTime) ? firstTime : secondTime;
        if(longerTime < BestFirstTime) {
            BestFirstTime = longerTime;
            solution.setTimeOfBestPermutationFirst(firstTime);
            solution.setTimeOfBestPermutationSecond(secondTime);
            solution.setRankedFirstMachine(firstMachine);
            solution.setRankedSecondMachine(secondMachine);
        }
        firstTime = 0;
        secondTime = 0;
        firstMachine.clear();
        secondMachine.clear();
    }

    return solution;
}

Solution Problem::dynamicProgramming()
{
    int sum = 0;
    int i, j;
    int firstTime = 0;
    int secondTime = 0;
    int num = this->numberOfTasks;
    std::vector<Task> allTasks = this->tasks;
    std::vector<Task> firstMachine;
    std::vector<Task> secondMachine;

    for (i = 0; i < num; i++)
        sum += (int)allTasks[i].getP();

    if (sum % 2 != 0)
        sum += 1;

    bool array[num + 1][sum / 2 + 1];

    for(i = 0; i <= num; i++){
        for(j = 0; j < sum/2; j++){
            if (j==0) array[i][j] = true;
            else array[i][j] = false;

        }

    }

    for(i = 1; i <= num; i++){
        for(j = 1; j < sum/2 + 1; j++) {
            if ((array[i - 1][j] == true) ||
                ((j >= allTasks[i - 1].getP()) && (array[i - 1][j - (int) allTasks[i - 1].getP()] == true))) {
                array[i][j] = true;
            }
        }
    }
    j -=1;
    while(j>0){
       int k=0;
        while(!array[k][j]){
            k++;
        }
        firstMachine.push_back(allTasks[k - 1]);
        firstTime += static_cast<int>(allTasks[k - 1].getP());
        j -= static_cast<int>(allTasks[k - 1].getP());
        allTasks.erase(allTasks.begin() + k - 1);
    }
    secondMachine = allTasks;

    for(Task task : secondMachine) secondTime += (int)task.getP();

    Solution solution("Dynamic",firstMachine,secondMachine,firstTime,secondTime);
    return solution;
}

Solution Problem::PTAS() {
    int count=3;

    std::vector<Task> firstMachine;
    std::vector<Task> secondMachine;
    std::vector<Task> allTasks = this->tasks;
    std::vector<Task> taskForCompleteOverview;
    std::vector<int> tmp;
    tmp.resize(count);

    allTasks = sortP(allTasks);

    for (int k = 0; k < count; k++){
        taskForCompleteOverview.push_back(allTasks[0]);
        allTasks.erase(allTasks.begin());
    }

    double firstTime =0;
    double secondTime =0;
    double BestFirstTime = DBL_MAX;
    double longerTime;

    generateAllBinaryStrings(count, tmp, 0);
    Solution solution("Ptas", firstMachine, secondMachine, BestFirstTime, 0);
    int counter =0;
    for(int i = 0; i < this->allCombinations.size()/2; i++){
        counter =0;
        for(int j : this->allCombinations[i]){
            if(j==0) {
                firstTime += taskForCompleteOverview[counter].getP();
                firstMachine.push_back(taskForCompleteOverview[counter]);
            }
            else {
                secondTime += taskForCompleteOverview[counter].getP();
                secondMachine.push_back(taskForCompleteOverview[counter]);
            }
            counter++;
        }
        longerTime = (firstTime > secondTime) ? firstTime : secondTime;
        if(longerTime < BestFirstTime) {
            BestFirstTime = longerTime;
            solution.setTimeOfBestPermutationFirst(firstTime);
            solution.setTimeOfBestPermutationSecond(secondTime);
            solution.setRankedFirstMachine(firstMachine);
            solution.setRankedSecondMachine(secondMachine);
        }
        firstTime = 0;
        secondTime = 0;
        firstMachine.clear();
        secondMachine.clear();
    }

    firstTime = solution.getTimeOfBestPermutationFirst();
    secondTime = solution.getTimeOfBestPermutationSecond();

    for (int i =0; i < allTasks.size(); i++) {
        if(firstTime <= secondTime) {
            firstMachine.push_back(allTasks[i]);
            firstTime += allTasks[i].getP();
        }else {
            secondMachine.push_back(allTasks[i]);
            secondTime += allTasks[i].getP();
        }
    }

    solution.setTimeOfBestPermutationFirst(firstTime);
    solution.setTimeOfBestPermutationSecond(secondTime);
    solution.setRankedFirstMachine(firstMachine);
    solution.setRankedSecondMachine(secondMachine);

    return solution;

}

Solution Problem::FPTAS() {
    int parameter = 8;

    std::vector<Task> allTasks = this->tasks;

    for(int i =0; i < tasks.size(); i++) {
        this->tasks[i].setP(this->tasks[i].getP()/parameter);
     }

    Solution solution = this->dynamicProgramming();


}

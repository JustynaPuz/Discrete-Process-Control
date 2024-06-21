#include "../inc/Problem.h"
#include<algorithm>

bool sortTimeKey ( Task task1, Task task2 ) {
    return (task1.getTime() < task2.getTime());
}
bool sortTimeJohnsonsAscKey ( Task task1, Task task2 ) {
    return (task1.getSpecificPJ(0) < task2.getSpecificPJ(0));
}

bool sortTimeJohnsonsDescKey ( Task task1, Task task2 ) {
    return (task1.getSpecificPJ(1) >= task2.getSpecificPJ(1));
}


std::vector<Task> Problem::sortTime(std::vector<Task> permutation) {
    std::sort(permutation.begin(), permutation.end(), sortTimeKey);
    return permutation;
}

std::vector<Task> Problem::sortJohnsonTime(std::vector<Task> permutation, bool isAscending) {
    if(isAscending) {
        std::sort(permutation.begin(), permutation.end(), sortTimeJohnsonsAscKey);
    } else {
        std::sort(permutation.begin(), permutation.end(), sortTimeJohnsonsDescKey);
    }
    return permutation;
}



void Problem::generateAllPermutation() {
    std::vector<int> indexes(tasks.size());
    for (int i = 0; i < tasks.size(); i++) {
        indexes[i] = i;
    }
    do {
        std::vector<Task> currentPermutation;
        for (int index: indexes) {
            currentPermutation.push_back(tasks[index]);
        }
        allPermutation.push_back(currentPermutation);

    } while (std::next_permutation(indexes.begin(), indexes.end()));
}

int Problem::calculateTime(std::vector<Task> permutation) {
    std::vector<int> endOfProcessTime;
    endOfProcessTime.reserve(this->numberOfMachines);

    for (int i = 0; i < numberOfMachines; i++) {
        endOfProcessTime.push_back(0);
    }

    for (int i = 0; i < permutation.size(); i++) {
        for (int j = 0; j < numberOfMachines; j++) {
            int time = permutation [i].getSpecificPJ(j);
            endOfProcessTime[j] += time;
            if(j<numberOfMachines-1 && endOfProcessTime[j+1]<endOfProcessTime[j]){
                endOfProcessTime[j+1]=endOfProcessTime[j];
            }
        }
    }
    return endOfProcessTime.back();
}

int Problem::completeOverview(){
    this->generateAllPermutation();

    int time = 0, bestTime = INT_MAX;
    for(std::vector<Task> task : allPermutation){
        time = calculateTime(task);
        if(time < bestTime){
            bestTime = time;
        }
    }
    return bestTime;
}

Solution Problem::NEH() {
    std::vector<Task> permutation = this->tasks;
    std::vector<Task> bestPerm;
    std::vector<Task> tmpPerm;
    int time = 0;
    int bestTime = 0;
    int endTime = 0;

    permutation = sortTime(permutation);

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
    Solution solution("Custom Algorithm", time, bestPerm);
    return solution;
}

Solution Problem::Johnson() {
    std::vector<Task> firstSet;
    std::vector<Task> secondSet;

    for(Task task : tasks) {
        if(task.getSpecificPJ(0) < task.getSpecificPJ(1)) {
            firstSet.push_back(task);
        }else if (task.getSpecificPJ(0) >= task.getSpecificPJ(1)) {
            secondSet.push_back(task);
        }
    }

    firstSet = sortJohnsonTime(firstSet,true);
    secondSet = sortJohnsonTime(secondSet,false);
    std::vector<Task> concatenatedVector(firstSet);
    concatenatedVector.insert(concatenatedVector.end(), secondSet.begin(), secondSet.end());

    int time = calculateTime(concatenatedVector);

    Solution solution = *new Solution("Johnson", time);
    return solution;

}

Solution Problem::FNeh() {
    std::vector<Task> allTasks = this->tasks;
    std::vector<Task> resultTasksInOrder;

    std::vector<std::vector<int>> resultFromLeft(numberOfMachines);
    std::vector<std::vector<int>> resultFromRight(numberOfMachines);
    std::vector<std::vector<int>> tmp;

    resultTasksInOrder.push_back(allTasks[0]);
    resultFromLeft[0].push_back(allTasks[0].getSpecificPJ(0));
    resultFromRight[0].push_back(allTasks[0].getSpecificPJ(numberOfMachines-1));

    for(int i=1; i< numberOfMachines; i++) {
        int time =allTasks[0].getSpecificPJ(i) + (resultFromLeft[i-1])[0];
        resultFromLeft[i].push_back(time);
    }

    int index =0;
    for(int i=numberOfMachines-2; i>=0; i--){
         int time =allTasks[0].getSpecificPJ(i) + (resultFromRight[index])[0];
        resultFromRight[++index].push_back(time);
    }

    int bestTime = INT_MAX;
    int bestIndex = -1;
    int actualNumberOfTasks = 1;
    for(int j = 1; j < numberOfTasks; j++) {

        for(int jj = 0; jj < actualNumberOfTasks + 1; jj++){

        }
    }

    Solution solution = *new Solution("FNEH", 1);
    return solution;
}

std::vector<std::vector<Task>> generateNeighbors(const std::vector<Task>& tasks) {
    std::vector<std::vector<Task>> result;
    for (size_t i = 0; i < tasks.size() - 1; ++i) {
        for (size_t j = i + 1; j < tasks.size(); ++j) {
            std::vector<Task> neighbor = tasks;
            std::swap(neighbor[i], neighbor[j]);
            result.push_back(neighbor);
        }
    }
    return result;
}

std::pair<int,int> findChange(std::vector<Task> firstVector, std::vector<Task> secondVector){
    std::pair<int,int> result;
    for(int i = 0; i < firstVector.size(); i++){
        if(firstVector[i].getIndex() != secondVector[i].getIndex()){
            for(int j = 0; j < firstVector.size(); j++) {
                if (firstVector[j].getIndex() == secondVector[i].getIndex()) {
                    result = std::make_pair(i,j);
                    return result;
                }
            }
        }
    }
}

Solution Problem::TabuSearch(std::vector<Task> initialSolution, int numOfIterations, int tabuListSize) {
    int numberOfIterations = numOfIterations;
    std::vector<std::pair<int,int>> tabuList;
    tabuList.reserve(tabuListSize);
    std::vector<Task> currentSolution = std::move(initialSolution);
    std::vector<Task> bestSolution = currentSolution;
    int bestTime = calculateTime(currentSolution);

    for(int i =0; i < numberOfIterations; i++) {
        std::vector<std::vector<Task>> neighbors = generateNeighbors(currentSolution);

        for(std::vector<Task> neighbor : neighbors){
            int neighborTime = calculateTime(neighbor);
            if(neighborTime < bestTime){
                std::pair<int,int> difference = findChange(currentSolution, neighbor);
                if(tabuList.size() > 0) {
                    for (std::pair<int, int> pair: tabuList) {
                        if (pair == difference) {
                            break;
                        }
                        tabuList.push_back(difference);
                        currentSolution = neighbor;
                        bestTime = neighborTime;
                    }
                }
                else {
                    tabuList.push_back(difference);
                    currentSolution = neighbor;
                    bestTime = neighborTime;
                }
            }
        }

    }
    Solution solution = *new Solution("TabuSearch", bestTime, currentSolution);
    return solution;
}

Solution Problem::thresholdAccepting(int numOfIterations, double initialThreshold, double decayRate) {
    std::vector<Task> currentSolution = tasks;  // Początkowa permutacja zadań
    std::vector<Task> bestSolution = currentSolution;
    double threshold = initialThreshold;

    int currentTime = calculateTime(currentSolution);
    int bestTime = currentTime;

    for (int i = 0; i < numOfIterations; i++) {
        std::vector<Task> newSolution = generateNeighbor(currentSolution);
        int newTime = calculateTime(newSolution);
        int delta = newTime - currentTime;

        if (delta < threshold) {  // Akceptacja gorszego rozwiązania w ramach progu
            currentSolution = newSolution;
            currentTime = newTime;
        }

        if (newTime < bestTime) {  // Aktualizacja najlepszego rozwiązania
                bestSolution = newSolution;
                bestTime = newTime;
            }
        // Aktualizacja progu
        threshold *= decayRate;
    }
    int time = calculateTime(bestSolution);

    Solution solution = *new Solution("tresholdAccepting",time, bestSolution);
    return solution;
}

// Funkcja generująca nowe rozwiązanie poprzez zamianę dwóch losowych zadań
std::vector<Task> Problem::generateNeighbor(const std::vector<Task>& solution) {
    std::vector<Task> newSolution = solution;
    int index1 = rand() % solution.size();
    int index2 = rand() % solution.size();
    std::swap(newSolution[index1], newSolution[index2]);
    return newSolution;
}




#include "../inc/Problem.h"
#include "../inc/Solution.h"
#include<algorithm>
#include <queue>
#include <iostream>

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
    bool operator()(const Task&  task1,const  Task& task2){
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
    double timeOfBestPermutation;

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

    Solution solution("Complete review", bestPermutation, timeOfBestPermutation);
    return  solution;
}

Solution Problem::schrage() {
    std::vector<Task> permutation = this->tasks;
    std::priority_queue<Task, std::vector<Task>, compareQ>  tasksByQ ;
    std::priority_queue<Task, std::vector<Task>, compareQ>  availableTasks;
    std::vector<Task> bestPermutation;

    for(Task task : permutation){
        tasksByQ.push(task);
    }
   /* for(int i =0; i < permutation.size(); i++) {
        Task t = pq.top();
        std::cout << t.getQ() << std::endl;
        pq.pop();
    }*/

   int time =0;
   while(!tasksByQ.empty() || !availableTasks.empty()) {
      while(!tasksByQ.empty() && tasksByQ.top().getR() <= time ) {
          availableTasks.push(tasksByQ.top());
          tasksByQ.pop();
      }

      if(availableTasks.empty()) {
          time = tasksByQ.top().getR();
      } else {
          Task task = availableTasks.top();
          availableTasks.pop();

          time += task.getP();
      }
       std::cout << "Time: " << time << std::endl;
   }

    std::cout << "Time: " << time << std::endl;
    Solution solution("Schrage", permutation, 0);
    return  solution;
}





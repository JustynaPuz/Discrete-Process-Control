
#include "../inc/Problem.h"
#include "../inc/Solution.h"
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

    std::cout << "Time: " << time << std::endl;
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


                /*//std::cout << permutation[0].getQ() << "<" << task.getQ() << std::endl;
                if(task.getQ() > permutation[0].getQ()){
                    permutation[0].setP(time-task.getR());
                    availableTasks.pop();
                    availableTasks.push(task);
                    time = task.getR();
                };
                //std::cout << task.getP() << std::endl;
                if(task.getP() > 0){
                    transferConditionally(tasksByQ,availableTasks,time);
                }*/
            } else {
                if(endTime < time + task.getQ()) {
                    endTime = time + task.getQ();
                }
                bestPermutation.push_back(task);
                task = availableTasks.top();
                availableTasks.pop();
            }
            availableTasks.push(task);

        }
    }


        /*if(availableTasks.empty()) {
        time = permutation[0].getR();
        } else {
            Task task = availableTasks.top();
            availableTasks.pop();
            bestPermutation.push_back(task);
            permutation.erase(std::remove_if(permutation.begin(), permutation.end(),[&task](Task x) {return x.getIndex() == task.getIndex();}),permutation.end());

            time += task.getP();
        }*/
    //time++;


    //std::cout << "t: " << time << std::endl;
    //time = calculateTime(bestPermutation)

    std::cout << "Time: " <<  time << " endTime: " << endTime<< std::endl;
    Solution solution("Schrage", permutation, calculateTime(bestPermutation));
    return  solution;
}
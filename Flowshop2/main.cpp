#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "inc/Problem.h"
#include "inc/Task.h"
#include "inc/Solution.h"
#include "inc/TestAlgorithm.h"


Problem ReadFile() {
    std::ifstream ReadFile("C://Users//Justyna//Desktop//Discrete-Process-Control//Flowshop2//resources//example1");
    if (ReadFile.is_open()) {
        int numberOfTasks = 0;
        int numberOfMachines = 0;
        std::vector<Task> tasks;
        std::string s = "";

        getline(ReadFile, s);

        std::vector<int> result;
        std::string temp;
        std::istringstream iss(s);
        while (iss >> temp) {
            int num = std::stoi(temp);
            result.push_back(num);
        }

        numberOfMachines = result.back();
        result.pop_back();
        numberOfTasks = result.back();
        result.pop_back();

        tasks.reserve(numberOfTasks);

        int i = 0;
        bool isIn = false;
        int time;
        for (int i = 0; i < numberOfTasks; i++) {
            Task task = *new Task(numberOfMachines, i);
            getline(ReadFile, s);
            std::istringstream iss(s);
            while (iss >> time) {
                if (isIn) {
                    task.addPJ(time);
                }
                isIn = !isIn;
            }
            tasks.push_back(task);
        }
        Problem problem(numberOfTasks, numberOfMachines, tasks);
        return problem;

    } else {
        return Problem();
    }
}

int main() {
    Problem problem = ReadFile();
  //  Solution completeOverview = *new Solution("CompleteOverview", problem.completeOverview());
   // Solution neh = problem.NEH();
   // Solution johnson = problem.Johnson();
   //Solution fNeh = problem.FNeh();
   //Solution tabuSearch = problem.TabuSearch(neh.getTasks(), 10, 5);
  // Solution thresholdAccepting = problem.thresholdAccepting( 10, 5,5);
    TestAlgorithm::test(problem);
    return 0;
}



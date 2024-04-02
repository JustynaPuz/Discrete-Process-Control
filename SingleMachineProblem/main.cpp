#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "inc/Problem.h"
#include "inc/Task.h"
#include "inc/Solution.h"
#include "inc/TestAlgorithm.h"

Problem ReadFile() {
    std::ifstream ReadFile("C:\\Users\\Justyna\\Desktop\\Discrete-Process-Control\\SingleMachineProblem\\resources\\example.txt");
    if (ReadFile.is_open()) {
        int number = 0;
        std::string s = "";

        getline(ReadFile, s);
        number = stoi(s);
        //  std::cout << s << std::endl;
        std::vector<Task> tasks;
        tasks.reserve(number);
        int i =0;
        while(!ReadFile.eof()){
            getline(ReadFile, s);
            std::istringstream iss(s);
            double p, r, q;
            iss >> r;
            iss >> p;
            iss >> q;
            Task task(p, r, q,i );
            tasks.push_back(task);
            i++;
        }
        Problem problem(number, tasks);
        return problem;

    }else{
        std::cout << "File error";
        return Problem();
    }
}

int main() {
    Problem problem = ReadFile();

    Solution  permutationSortR = problem.permutationSortR();
    std::cout << permutationSortR << std::endl;

    Solution  permutationSortQ = problem.permutationSortQ();
    std::cout << permutationSortQ << std::endl;

    Solution permutationSchrage = problem.schrage();
    std::cout << permutationSchrage << std::endl;

    Solution theBest = problem.puzAndOwczarekMethod();
    std::cout << theBest << std::endl;

    Solution permutationBetterSchrage = problem.betterSchrage();
    std::cout << permutationBetterSchrage << std::endl;

    TestAlgorithm::test(problem);
    return 0;

}

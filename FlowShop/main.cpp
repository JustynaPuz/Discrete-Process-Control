#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "inc/Problem.h"
#include "inc/Task.h"
#include "inc/Solution.h"


Problem ReadFile() {
    std::ifstream ReadFile("resources/example1");
    if (ReadFile.is_open()) {
        int number = 0;
        int numberOfMachines=0;
        std::vector<Task> tasks;
        std::string s = "";

        getline(ReadFile, s);

        std::vector<int> result;
        std::string temp;
        std::istringstream iss(s);
        while(iss >> temp) {
            int num = std::stoi(temp);
            result.push_back(num);
        }

        numberOfMachines = result.back();
        number = result.back();

        std::cout << s << std::endl;

        tasks.reserve(number);
        int i =0;
        while(!ReadFile.eof()){
            getline(ReadFile, s);
            std::istringstream iss(s);
            double p, r, q;
            iss >> p;
            iss >> r;
            iss >> q;
            Task task(p, r, q,i );
            tasks.push_back(task);
            i++;
        }
        Problem problem(number, tasks);
        return problem;

    }else{
        return Problem();
    }
}

int main() {

    Problem problem = ReadFile();
    //problem.generateAllPermutation();
    /* problem.sortR();
     problem.sortQ();*/
    return 0;
}



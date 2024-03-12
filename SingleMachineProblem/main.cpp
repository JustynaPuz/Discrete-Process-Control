#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "inc/Problem.h"
#include "inc/Task.h"
#include "inc/Solution.h"


Problem ReadFile() {
    std::ifstream ReadFile("C:/Users/Justyna/Desktop/example.txt");
    if (ReadFile.is_open()) {
        int number = 0;

        std::string s = "";

        getline(ReadFile, s);
        number = stoi(s);
        std::cout << s << std::endl;
        std::vector<Task> tasks;
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
    problem.generateAllPermutation();
   /* problem.sortR();
    problem.sortQ();*/
    return 0;
}



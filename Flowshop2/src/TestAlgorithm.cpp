//
// Created by Justyna on 02.04.2024.
//
#include "../inc/TestAlgorithm.h"
#include <chrono>
#include <iostream>


void TestAlgorithm::test(Problem problem) {

    //NEH
    auto start = std::chrono::high_resolution_clock::now();
    Solution neh = problem.NEH();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds >(end - start);

    std::cout<< neh << " Czas: " << duration.count() << std::endl;

    //Johnson
    start = std::chrono::high_resolution_clock::now();
    Solution johnson = problem.Johnson();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout<< johnson  << " Czas: " << duration.count() << std::endl;

    //TabuSearch
    start = std::chrono::high_resolution_clock::now();
    Solution tabuSearch = problem.TabuSearch(neh.getTasks(), 10, 5);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout<< tabuSearch << " Czas: " << duration.count() << std::endl;

    //Threshold
    start = std::chrono::high_resolution_clock::now();
    Solution thresholdAccepting = problem.thresholdAccepting( 10, 5,5);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout<< thresholdAccepting << " Czas: " << duration.count() << std::endl;




//        //Complete
//     start = std::chrono::high_resolution_clock::now();
//    Solution completeOverview = *new Solution("CompleteOverview", problem.completeOverview());
//     end = std::chrono::high_resolution_clock::now();
//     duration = std::chrono::duration_cast<std::chrono::microseconds >(end - start);
//    std::cout << completeOverview << " Czas: " << duration.count() << std::endl;;



}


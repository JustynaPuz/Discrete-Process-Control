//
// Created by Justyna on 02.04.2024.
//
#include "../inc/TestAlgorithm.h"
#include <chrono>



void TestAlgorithm::test(Problem problem) {
    //LSA
    auto start = std::chrono::high_resolution_clock::now();
    Solution  permutationLSA = problem.LSA();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds >(end - start);
    std::cout << permutationLSA << " Czas: " << duration.count() << std::endl;;

    //LPT
    start = std::chrono::high_resolution_clock::now();
    Solution  permutationLPT = problem.LPT();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds >(end - start);

    std::cout<< permutationLPT << " Czas: " << duration.count() << std::endl;

    //Dynamic Programming
    start = std::chrono::high_resolution_clock::now();
    Solution permutationDynamic = problem.dynamicProgramming();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout<< permutationDynamic  << " Czas: " << duration.count() << std::endl;

    //PTAS
    start = std::chrono::high_resolution_clock::now();
    Solution permutationPTAS= problem.PTAS();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout<< permutationPTAS << " Czas: " << duration.count() << std::endl;


    //Complete Overview
    /*start = std::chrono::high_resolution_clock::now();
    Solution  allPermutation = problem.CompleteOverview();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout<< allPermutation << " Czas: " << duration.count() << std::endl;*/



}


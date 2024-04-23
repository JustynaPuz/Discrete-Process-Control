//
// Created by Justyna on 02.04.2024.
//
#include "../inc/TestAlgorithm.h"
#include <chrono>
/*

void TestAlgorithm::test(Problem problem) {
    //SORT R
    auto start = std::chrono::high_resolution_clock::now();
    Solution  permutationSortR = problem.permutationSortR();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds >(end - start);
    std::cout<< "Algorithm: " << permutationSortR.getCriterium() << " Criterion: " << permutationSortR.getTimeOfBestPermutation()<<
             " Duration in microseconds " << duration.count() << std::endl;

    //SORT Q
    start = std::chrono::high_resolution_clock::now();
    Solution  permutationSortQ = problem.permutationSortQ();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds >(end - start);

    std::cout<< "Algorithm: " << permutationSortQ.getCriterium() << " Criterion: " << permutationSortQ.getTimeOfBestPermutation()<<
             " Duration in microseconds " << duration.count() << std::endl;

    //all permutation
    start = std::chrono::high_resolution_clock::now();
    Solution  allPermutation = problem.generatePermutation();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout<< "Algorithm: " << allPermutation.getCriterium() << " Criterion: " << allPermutation.getTimeOfBestPermutation()<<
             " Duration in microseconds " << duration.count() << std::endl;
    //Schrage
    start = std::chrono::high_resolution_clock::now();
    Solution permutationSchrage = problem.schrage();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout<< "Algorithm: " << permutationSchrage.getCriterium() << " Criterion: " << permutationSchrage.getTimeOfBestPermutation()<<
             " Duration in microseconds " << duration.count() << std::endl;

    //BetterSchrage
    start = std::chrono::high_resolution_clock::now();
    Solution permutationBetterSchrage = problem.betterSchrage();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout<< "Algorithm: " << permutationBetterSchrage.getCriterium() << " Criterion: " << permutationBetterSchrage.getTimeOfBestPermutation()<<
             " Duration in microseconds " << duration.count() << std::endl;

    //Own algorithm
    start = std::chrono::high_resolution_clock::now();
    Solution theBest = problem.puzAndOwczarekMethod();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout<< "Algorithm: " << theBest.getCriterium() << " Criterion: " << theBest.getTimeOfBestPermutation()<<
             " Duration in microseconds " << duration.count() << std::endl;
}
*/

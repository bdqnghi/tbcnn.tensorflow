#define _USE_MATH_DEFINES
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

#include "TestCases.hpp"








double totalSin() {
    double total = 0; for (double angle = 0; angle < 1000000; angle += M_PI / 100.0) {
        total += std::sin(angle);
    } return total;
}

std::vector<int> createVector(int length){
    std::vector<int> returnVector;
    
    for (unsigned int i = 0; i < length; i++){
        returnVector.push_back((rand() % length) + 1);
    }
    
    return returnVector;
}

SortStats bubbleSort(std::vector<int>& sortVector){
    SortStats bubbleSortStats = {0, 0, 0};



    
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start =
    std::chrono::high_resolution_clock::now();
    
    bool swapped = false;
    
    do{
        swapped = false;
        for (unsigned int i = 0; i < sortVector.size() - 1; i++){
            bubbleSortStats.compareCount++;
            if (sortVector[i] > sortVector[i + 1]){
                std::swap(sortVector[i], sortVector[i + 1]);
                bubbleSortStats.swapCount++;
                swapped = true;
            }
        }
        
    }while(swapped);
    
    
    std::chrono::time_point<std::chrono::high_resolution_clock> end =
    std::chrono::high_resolution_clock::now();
    
    
    std::chrono::duration<double> time = end - start;
    bubbleSortStats.time = time.count();
    return bubbleSortStats;
}

SortStats selectionSort(std::vector<int>& sortVector){
    SortStats selectionSortStats = {0, 0, 0};



    
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start =
    std::chrono::high_resolution_clock::now();
    
    for (unsigned int i = 0; i < sortVector.size() - 1; i++){
        unsigned int minimum = i;
        
        for (unsigned int k = i; k < sortVector.size(); k++){
            selectionSortStats.compareCount++;
            if (sortVector[minimum] > sortVector[k]){
                minimum = k;
            }
          }
            std::swap(sortVector[minimum], sortVector[i]);
            selectionSortStats.swapCount++;
    }
    
    
    std::chrono::time_point<std::chrono::high_resolution_clock> end =
    std::chrono::high_resolution_clock::now();
    
    
    std::chrono::duration<double> time = end - start;
    selectionSortStats.time = time.count();
    return selectionSortStats;
}


void runTestCases()
{
    executeTest(testCase1, bubbleSort, "Bubble Sort: 10 items");
    executeTest(testCase2, bubbleSort, "Bubble Sort: 500 items");
    executeTest(testCase3, bubbleSort, "Bubble Sort: 100 to 1000 items");
    
    executeTest(testCase1, selectionSort, "Selection Sort: 10 items");
    executeTest(testCase2, selectionSort, "Selection Sort: 500 items");
    executeTest(testCase3, selectionSort, "Selection Sort: 100 to 1000 items");
    
    executeTest(testCaseCompare, bubbleSort, selectionSort, "Sort Compare Test");
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    runTestCases();
    
    
    std::cout << std::endl << "--- Timing Results ---" << std::endl << std::endl;
    for (unsigned int i = 100; i <= 1000; i+=100){
        std::vector<int> useThisVectorBubble = createVector(i);
        std::vector<int> useThisVectorSelection = createVector(i);
        SortStats bubbleSortStats = bubbleSort(useThisVectorBubble);
        SortStats selectionSortStats = selectionSort(useThisVectorSelection);
        
        std::cout << "Number of Items     : " << i << std::endl;
        std::cout << "Bubble Sort Time    : " << bubbleSortStats.time << " seconds" << std::endl;
        std::cout << "Selection Sort Time : " << selectionSortStats.time << " seconds" << std::endl << std::endl;
        
    }
    return 0;
}



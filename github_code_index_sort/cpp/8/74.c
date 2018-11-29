//==============================================================================
// CS 560 Project - Quicksort Analysis
//==============================================================================
/*
    File: quicksort.cpp
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS560 - Spring 2018
    Date: 4/14/2018

******************************************************************************/

#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <chrono>
#include "quicksort.h"
#include "output.h"

const int QuickSort::MAX_RANGE = 10000;
const int QuickSort::TIMES_TO_RUN = 5;
const int QuickSort::DEFAULT_X = 2;
std::vector<int> QuickSort::N_VALS = {10, 100, 1000, 10000};

void QuickSort::quicksort(std::vector<int> &arr) {
    return QuickSort::quicksort(arr, 0, arr.size()-1);
}

void QuickSort::rand_quicksort(std::vector<int> &arr) {
    return QuickSort::rand_quicksort(arr, 0, arr.size()-1);
}

void QuickSort::populate_increasing_array(std::vector<int> &arr, int n, int x) {
    if (n < 1) {
        throw std::invalid_argument("n is not valid.");  // Invalid n
    }
    arr.clear();
    for (int i = 0; i < n; i++) {
        arr.push_back(n + (i * x));
    }
}

void QuickSort::populate_random_array(std::vector<int> &arr, int n) {
    if (n < 1) {
        throw std::invalid_argument("n is not valid.");  // Invalid n
    }
    srand(time(NULL));
    arr.clear();
    for (int i = 0; i < n; i++) {
        int val = rand() % QuickSort::MAX_RANGE;
        arr.push_back(val);
    }
}

void QuickSort::populate_array(std::vector<int> &arr, ArrayType arrayType, int n, int x)
{
    if (arrayType == ArrayType::RANDOM) {
        QuickSort::populate_random_array(arr, n);
    } else if (arrayType == ArrayType::INCREASING){
        QuickSort::populate_increasing_array(arr, n, x);
    } else {
        throw std::invalid_argument("Sort Type is not valid.");
    }
}

double QuickSort::calc_runtime(std::vector<int> &arr, SortType sortType)
{
    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
    if (sortType == SortType::STANDARD) {
        QuickSort::quicksort(arr);
    } else if (sortType == SortType::RANDOM) {
        QuickSort::rand_quicksort(arr);
    } else {
        throw std::invalid_argument("Sort Type is not valid.");
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    double duration = (double)std::chrono::duration_cast<std::chrono::microseconds>( end - begin ).count();
    return duration / 1000;
}

void QuickSort::compile_report(std::string filepath)
{
    // Initialize permutations
    std::vector< std::pair<ArrayType, SortType> > perms{
        {ArrayType::INCREASING, SortType::STANDARD},
        {ArrayType::INCREASING, SortType::RANDOM},
        {ArrayType::RANDOM, SortType::STANDARD},
        {ArrayType::RANDOM, SortType::RANDOM},
    };

    // Iterate through all array and sort permutations
    std::vector< std::vector<double> > all_ave_times;
    for (std::vector< std::pair<ArrayType, SortType> >::iterator i = perms.begin(); i != perms.end(); i++) {

        // Iterate through all N sizes
        std::vector<double> n_ave_times;
        for (std::vector<int>::iterator j = QuickSort::N_VALS.begin(); j != QuickSort::N_VALS.end(); j++) {

            // Generate average time for n value with permutation
            double total_time = 0;
            for (int k = 0; k < QuickSort::TIMES_TO_RUN; k++) {
                std::vector<int> sort_arr;
                QuickSort::populate_array(sort_arr, i->first, *j, QuickSort::DEFAULT_X);
                total_time += QuickSort::calc_runtime(sort_arr, i->second);
            }
            n_ave_times.push_back(total_time / QuickSort::TIMES_TO_RUN);
        }
        all_ave_times.push_back(n_ave_times);
    }
    Output::output_to_csv(all_ave_times, filepath);
}

int QuickSort::partition(std::vector<int> &arr, int p, int r) {
    int x = arr[p];
    int i = p;
    int j = r + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] <= x && i < j);
        do {
            j--;
        } while (arr[j] >= x && j >= i);
        if (i < j) {
            std::swap(arr[i], arr[j]);
        } else {
            break;
        }
    }
    std::swap(arr[p], arr[j]);
    return j;
}

void QuickSort::quicksort(std::vector<int> &arr, int p, int r) {
    if (p < r) {
        int q = QuickSort::partition(arr, p, r);
        QuickSort::quicksort(arr, p, q-1);
        QuickSort::quicksort(arr, q+1, r);
    }
}

int QuickSort::rand_partition(std::vector<int> &arr, int p, int r) {
    srand(time(NULL));
    int index = (rand() % (r-p)) + p;
    std::swap(arr[p], arr[index]);
    return QuickSort::partition(arr, p, r);
}

void QuickSort::rand_quicksort(std::vector<int> &arr, int p, int r) {
    if (p < r) {
        int q = QuickSort::rand_partition(arr, p, r);
        QuickSort::rand_quicksort(arr, p, q-1);
        QuickSort::rand_quicksort(arr, q+1, r);
    }
}



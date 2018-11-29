/*
    insertion-sort.cpp

    Created by Iran Neto on 20/10/18.

    This code implements the insertion sort algorithm with positive numbers.
    It works by taking one element, analyzing the vector to define where insert it.
    To compile you must use g++ or gcc and also set a flag to c++11:
    
    g++ insertion-sort.c -o exec -std=c++11

    To run: ./exec vectorSize MAX_VALUE
    Example: ./insertion 10 100

    Extra: Use time command from Unix Operating Systems for efficiency measurements

    Best case: Vector already sorted - O(n)
    Worst case: Vector is reversed order = O(n²)
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>

int MAX_VALUE; //needs to be global

int getParameters(int* N, int* MAX_VALUE, int argc, char* argv[]){
    //get parameters
    if(argc == 3){
        *N = atoi(argv[1]);
        *MAX_VALUE = atoi(argv[2]);
        std::cout << "Vector size: "<< *N << std::endl;
        return 0;
    }
    return -1;
}

int randIt(){ return (std::rand()%MAX_VALUE); }

int main(int argc, char* argv[]){
    int N, res;
    srand(time(NULL));
    
    res = getParameters(&N,&MAX_VALUE,argc,argv);
    if(res != 0){
        std::cout << "Specify size and max_value... " << std::endl;
        std::cout << " ./exec vectorSize MAX_VALUE" << std::endl;
        exit(1);
    }
    
    std::vector<int> vec(N);
    std::generate(vec.begin(), vec.end(), randIt);

    std::cout << "[";
    for(auto it: vec){ std::cout << " " << it << " ";}
    std::cout << "]" << std::endl << " Sorting... " << std::endl;

    /* vector.end() == V[N] - vector last element is in vector.end()-1 */
    //insertion-sort
    std::vector<int>::iterator it, it2, temp;
    for(it = vec.begin(); it != vec.end()-1; ++it){
        it2 = it + 1;
        std::cout << &it << "- it: " << *it << " " << &it2 << " - it2: " << *it2 << " - it2-1: " << *(it2-1) << std::endl;
        while(it2 != vec.begin() && *it2 < *(it2 - 1)){
            std::swap(*(it2-1),*temp);
            --it2;
        }
    }

    //print it sorted
    std::cout << "["; 
    for(auto it: vec){ std::cout << " " << it << " ";}
    std::cout << "]" << std::endl;
}
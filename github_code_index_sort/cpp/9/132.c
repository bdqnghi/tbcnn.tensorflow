/*  Name: Paul Talaga
    Date: Sept 9, 2018
    Desc: Selection sort timer example
    
    Compile as: g++ selection.cpp timer.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "timer.h"

const unsigned MAX_LENGTH = 1000;

using namespace std;

// Make the timer global so we don't have to pass it in.
Timer t;

// Sorts the vector via the selection sort method
void selectionSort(vector<int> &a){
    for(unsigned i = 0; i < a.size() - 1; i++){
        // Search the rest of the vector for the smallest item
        unsigned smallest_i = i;
        int smallest_value = a[i];
        for(unsigned j = i + 1; j < a.size(); j++){
            if( smallest_value > a[j]){
                smallest_i = j;
                smallest_value = a[j];
            }
        }
        // swap i with smallest_i
        int temp = a[i];
        a[i] = a[smallest_i];
        a[smallest_i] = temp;
        t.incrementA(); // Log the swap
    }
}


int main(){
    
    srand(time(0));
    
    vector<int> a;
    
    // Evaluate different vector lengths
    for(unsigned length = 1; length < MAX_LENGTH; length++){
        // Always start with empty vectors
        a.clear();
    
        // Fill in the vectors with random numbers
        for(unsigned i = 0; i < length; i++){
            a.push_back(rand() % 10000);
        }
        
        
        t.setN(length);
        t.tic();
        // Sort
        selectionSort(a);
        t.toc();
        
        // Verify the operation worked
        for(unsigned i = 0; i < length-1; i++){
            if(a.at(i) > a.at(i+1)){
                cout << "Error!" << endl;
            }
        }
    }
    t.saveResults("times.csv");
}
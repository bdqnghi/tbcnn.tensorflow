#include "q3quicksort.h"
#include <uC++.h>
#include <iostream>
using namespace std;

//-------------------Quicksort::Quicksort--------------------------
// Purpose: Constructor -- initialize all private members
//
// Return:
//------------------------------------------------------------------
template<> Quicksort<TYPE>::Quicksort(TYPE values[], int low, int high, int depth) : values(values), low(low), high(high), depth(depth){
    
}

//-------------------Quicksort::~Quicksort--------------------------
// Purpose: Destructor
//
// Return:
//------------------------------------------------------------------
template<> Quicksort<TYPE>::~Quicksort(){
    
}

//-------------------Quicksort::partition--------------------------
// Purpose: find the partition of (sub) list of numbers
//
// Return: Integer
//------------------------------------------------------------------
template<> int Quicksort<TYPE>::partition(int lo, int hi){
    unsigned int index = lo + (hi-lo)/2; // choose a index of pivot
    TYPE pivot = values[index]; // get the value of pivot
    TYPE tmp;
    int i = lo - 1;
    
    // swap the value of pivot and the last element in this sublist
    tmp = values[hi];
    values[hi] = values[index];
    values[index] = tmp;
    
    
    for(int j = lo; j < hi; j++){
        if(values[j]<=pivot){
            i += 1; // keep tracking the last one equal or smaller than pivot
            tmp = values[i];
            values[i] = values[j];
            values[j] = tmp;
        }
    }
    //swap the value of pivot and the first one that larger than pivot
    tmp = values[i+1];
    values[i+1] = values[hi];
    values[hi] = tmp;
    return i+1;//return the pivot index
}

//-------------------Quicksort::start--------------------------
// Purpose: start to do quicksort for the list of values
//
// Return:
//------------------------------------------------------------------
template<> void Quicksort<TYPE>::Start(int lo, int hi){
    if(hi<0) return;
    int p;
    if(lo < hi){
        p = this->partition(lo, hi);
        if(depth > 0){// if the depth is larger than zero, create a thread
                      // to do quicksort of half of the list
            Quicksort<TYPE> quicksort(this->values, lo, p-1, --this->depth);
            Start(p+1, hi);
        }
        else{//sequential call
            Start(lo, p-1);
            Start(p+1, hi);
        }
    }
}

//-------------------Quicksort::main--------------------------
// Purpose: the execution method of this(object) task
//
// Return:
//------------------------------------------------------------------
template<> void Quicksort<TYPE>::main(){
    Start(this->low, this->high);
}


unsigned int uDefaultStackSize() {
    return 512 * 1000;        // set task stack-size to 512K
}
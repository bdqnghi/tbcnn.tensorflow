#include "q3quicksort.h"
#include <uC++.h>
#include <iostream>
using namespace std;






template<> Quicksort<TYPE>::Quicksort(TYPE values[], int low, int high, int depth) : values(values), low(low), high(high), depth(depth){
    
}






template<> Quicksort<TYPE>::~Quicksort(){
    
}






template<> int Quicksort<TYPE>::partition(int lo, int hi){
    unsigned int index = lo + (hi-lo)/2; 
    TYPE pivot = values[index]; 
    TYPE tmp;
    int i = lo - 1;
    
    
    tmp = values[hi];
    values[hi] = values[index];
    values[index] = tmp;
    
    
    for(int j = lo; j < hi; j++){
        if(values[j]<=pivot){
            i += 1; 
            tmp = values[i];
            values[i] = values[j];
            values[j] = tmp;
        }
    }
    
    tmp = values[i+1];
    values[i+1] = values[hi];
    values[hi] = tmp;
    return i+1;
}






template<> void Quicksort<TYPE>::Start(int lo, int hi){
    if(hi<0) return;
    int p;
    if(lo < hi){
        p = this->partition(lo, hi);
        if(depth > 0){
                      
            Quicksort<TYPE> quicksort(this->values, lo, p-1, --this->depth);
            Start(p+1, hi);
        }
        else{
            Start(lo, p-1);
            Start(p+1, hi);
        }
    }
}






template<> void Quicksort<TYPE>::main(){
    Start(this->low, this->high);
}


unsigned int uDefaultStackSize() {
    return 512 * 1000;        
}
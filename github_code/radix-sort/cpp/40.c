//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


int power(int base, int power){
    if ( power == 0 ) { return 1; }
    else {
        int value = base;
        for ( int i = 1; i < power; ++i ) {
            value = value * base;
        }
        return value;
    }
}

int mod_num(int n, int exponent){
    if ( exponent > 1 ) {
        return n % power(10,exponent) - n % power(10,exponent-1);
    }
    if ( exponent == 1 ) { return n % 10; }
}

void
RadixSort::sort(int A[], int size)
{
    double max = 0.0;
    for ( int i = 0; i < size; ++i ){
        if (A[i] > max) { max = A[i]; }
    }
 
	double list_max_size = log10(max)+1;
	
    for ( int i = 1; i <= list_max_size; ++i ){
        vector<int> arrayB (10,0);
		
        for ( int j = 0; j < size; ++j ){
            int tmp = mod_num(A[j],i)/(power(10,i-1));
            ++arrayB[tmp];
		}		
		
		for ( int j = 0; j < arrayB.size(); ++j ) {
			if (j==0) { arrayB[j] = arrayB[j]; }
			else if ( j>0 ) {
				arrayB[j] = arrayB[j] + arrayB[j-1]; 
			}
		}
		
		int indexA;
		int check=0;
		int arrayC[size];
		for ( int j = 0; j < size; ++j ) {
			int tmp = mod_num(A[j],i)/(power(10,i-1));
			if ( tmp == 0 ){
				arrayC[check] = A[j];
				++check;
			}
			if ( tmp > 0 ){
				indexA = arrayB[tmp-1];
				++arrayB[tmp-1];
				arrayC[indexA] = A[j];
			}
		}
		
		for(int j = 0; j<size; j++){
			A[j] = arrayC[j];
			cout << A[j] << endl;
		}
		
    }
        
  /*
     Complete this function with the implementation of radix sort
     algorithm.
  */
  
}

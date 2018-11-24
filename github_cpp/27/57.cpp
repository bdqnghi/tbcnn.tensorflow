//============================================================================
// Name        : radix-sort.cpp
// Author      : Xinyi(Kathy) Zhang
// Date        : 2/10/2015
// Copyright   : Most parts are original, but partially based on the counting sort algorithm in Leyk's notes
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstring>

using namespace std; 

int get_min(int* A, int size){
	int min = 0;
  		for(int i=0; i<size; ++i){
    		if(A[i]<min)
     		min = A[i];
     	}
     return min; 
}

bool check_negative(int min){
	if(min<0)
		return true;
	else return false;
	}

int get_max(int* A, int size){
		int max = 1;
  		for(int i=0; i<size; ++i){
    		if(A[i]>max)
     		max = A[i];
     	}
     	return max;
}


int get_max_digit(int max){
	return log10(max)+1;
}



void csort_for_rank(int* A, int size, int k, int r){// k is the range and r is the rank

	int B[size];
	int C[k];
	for(int i = 0; i < k; i++) C[i] = 0;// initialize array C to be all zero

	/*count the occurrence of the value of A[j] at rank r*/
	for(int j = 0; j < size; j++) C[A[j]/r%10] ++; 
	//we only compare the values on the same rank
	//value() function is to get the value of A[j] at rank r	

	for(int i = 1; i < k; i++) C[i] += C[i-1];//increment C array
	for(int j = size -1; j >= 0; j--){
		int v = A[j]/r%10;
		int index = C[v] - 1;//index of B array
		C[v]--;
		B[index] = A[j]; 
	}	
	
	memcpy(A, B, size*sizeof(int));//put sorted array back to A to repeatedly sort for the next rank


}

void
RadixSort::sort(int A[], int size)
{
	/*firstly, check whether array A contains negative number and if it does, shift all the integers to positive*/
	int min = get_min(A, size);
	if(check_negative(min)){
		for(int i = 0; i<size; i++){
			A[i]-=min;//add -min() to all intergers to the smallest negative number zero 
		}
	}

	int max = get_max(A, size);
	int max_dig = get_max_digit(max);//find the maximum digit 

	/*orting on each digit(rank) from least(right most) to left
	based on stable counting sort*/

	int k = 10;//range on one digit
	

	for(int c = 1, r = 1; c <= max_dig; c++, r *= 10){

		csort_for_rank(A, size, k, r);
	}  

	
  /*
     Complete this function with the implementation of radix sort
     algorithm.
  */
}









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



void csort_for_rank(int* A, int size, int k, int r){

	int B[size];
	int C[k];
	for(int i = 0; i < k; i++) C[i] = 0;

	
	for(int j = 0; j < size; j++) C[A[j]/r%10] ++; 
	
	

	for(int i = 1; i < k; i++) C[i] += C[i-1];
	for(int j = size -1; j >= 0; j--){
		int v = A[j]/r%10;
		int index = C[v] - 1;
		C[v]--;
		B[index] = A[j]; 
	}	
	
	memcpy(A, B, size*sizeof(int));


}

void
RadixSort::sort(int A[], int size)
{
	
	int min = get_min(A, size);
	if(check_negative(min)){
		for(int i = 0; i<size; i++){
			A[i]-=min;
		}
	}

	int max = get_max(A, size);
	int max_dig = get_max_digit(max);

	

	int k = 10;
	

	for(int c = 1, r = 1; c <= max_dig; c++, r *= 10){

		csort_for_rank(A, size, k, r);
	}  

	
  
}

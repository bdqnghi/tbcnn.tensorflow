//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <tgmath.h>
#include <deque>
//#include <fstream>

using namespace std;
//ofstream out;

const int base = 10; 
int digit(int k, int num)
{
	int r; 
	r = num/(int)pow(base, k);
	return r % base;
}

//deque <int>::reverse_iterator riter;
deque<int> mergeArr(deque<int> A,deque<int> B){
    deque <int> AB;
    
    
    for (int i=0; i<B.size(); i++){
        AB.push_back(B[i]);
    }
    
    for (int i= 0; i<A.size(); i++){
        AB.push_front(A[i]);
    }
	//for generating sorted output in reverse order for future testing
	/*
	out.open("1000_dec_output.txt");
	out<<"1000\n";
    for(riter=AB.rbegin(); riter!=AB.rend(); ++riter) {
        out << *riter << endl; // generate output in decreasing order
	}
	out.close();   */
    return AB;
}

void radixsort(deque<int>& A, int size){
    int d = 5; //radix sort can sort up to 2^15-1 = 32767
    int i, j, m;
    int *C = new int[base];
    int *B = new int[size];
    for(m = 0; m < d; m++){
        for(i = 0; i < base; i++) C[i] = 0;
        for(j = 0; j < size; j++) C[digit(m, A[j])]++;
        for(i = 1; i < base; i++) C[i] += C[i-1];
        for(j = size-1; j >= 0; j--){
            i = C[digit(m, A[j])]--;
            i--;
            B[i] = A[j];
        }
        for (j=0; j<size; j++) A[j] = B[j];
    }
    delete[] B; delete[] C;
    
}


void
RadixSort::sort(int A[], int size)
{
    try{
        deque<int> positive;
        deque<int> negative;
        
        for (int e=0; e<size; e++){
            if(A[e]<-32768 || A[e]>32767) throw ("Invalid input, Radix sort can only take numbers -2^15 to 2^15-1");
            if (A[e]<0) {
                negative.push_back(A[e]);
            } else {
                positive.push_back(A[e]);
            }
        }
        if (positive.size()>1){
            radixsort(positive,positive.size());
        }
        //sorting negative, make it positive and insert inversely
        if (negative.size()>1){
            for (int i=0; i<negative.size();i++){
                negative[i]*=-1;
            }
            radixsort(negative,negative.size());
            
            for (int i=0; i<negative.size();i++){
                negative[i]*=-1;
            }
        }
        
        deque<int> result(size);
        result=mergeArr(negative,positive);
        
        positive.clear(); positive.shrink_to_fit();
        negative.clear(); negative.shrink_to_fit();
        
        copy(result.begin(), result.end(),A);
        
    } catch(char const* msg){
        cout<<"Error: "<<msg<<endl;
        exit(EXIT_FAILURE);
    }
    
}





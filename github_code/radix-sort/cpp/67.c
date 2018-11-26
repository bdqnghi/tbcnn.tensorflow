//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include "math.h"

using namespace std;
const static int BASE = 10;
int digit(const int& k, const int& num) {
    int r;
    r = num/(int)(k);
    return r%BASE;
}
void RadixSort::sort(int A[], int n) {
    int i, j, m, d = 10, pos = 0;
    //for (int t = 0; t < n; t++) pos += abs(A[t]);
    //for (int t = 0; t < n; t++) A[t] += pos;
    //for (int t = 0; t < n; t++) d += (A[t] == 0) ? 1 : (int)log10(A[t]) + 1;
    //d = (int)ceil((double)d/n);
    int* C=new int[BASE*sizeof(int)];
    int* B=new int[n*sizeof(int)];
    for (m = 0; m < d; m++) {
        int k = (int)pow(BASE,m);
        for (i = 0; i < BASE; i++) C[i] = 0;
        for (j = 0; j < n; j++)  C[digit(k, A[j])]++;
        for (i = 1; i < BASE; i++)  C[i] += C[i-1];
        for (j = n-1; j >=0; j--) {
            i = C[digit(k, A[j])]--;
            B[i-1] = A[j];
        }
        for (j = 0; j < n; j++) A[j] = B[j];
    }
    //for (int t = 0; t < n; t++) A[t] -= pos;
    free(B), free(C);
}

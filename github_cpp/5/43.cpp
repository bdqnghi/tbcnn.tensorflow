







#include "insertion-sort.hpp"
#include <iostream>
using namespace std;

void insertion_sort(int* A, int A_length)
{
    int i;
    int key;
    for (int j = 1; j < A_length; j++) {
        key = A[j];
        
        i = j-1;
        while (A[i] > key && i > -1 ) {
            A[i + 1] = A[i];
            i--;
        }
        A[i+1] = key;
    }
}
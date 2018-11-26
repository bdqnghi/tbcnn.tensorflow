//
//  insertion-sort.cpp
//  sort-algorithm
//
//  Created by Meilei Jiang on 10/4/15.
//  Copyright © 2015 Meilei Jiang. All rights reserved.
//

#include "insertion-sort.hpp"
#include <iostream>
using namespace std;

void insertion_sort(int* A, int A_length)
{
    int i;
    int key;
    for (int j = 1; j < A_length; j++) {
        key = A[j];
        // insert A[j] into the sorted array A[1..j-1]
        i = j-1;
        while (A[i] > key && i > -1 ) {
            A[i + 1] = A[i];
            i--;
        }
        A[i+1] = key;
    }
}
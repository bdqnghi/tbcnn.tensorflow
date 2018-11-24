//============================================================================
// Name        : shell-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
using namespace std;

void
ShellSort::sort(int A[], int size)
{
cout << "shell sort!" << endl;
int temp = 0;
 num_cmps = 0;
 int step = size/2;
 while(step > 0)
 {
	++num_cmps;
	for(int i = step; i < size; ++i)
	{
		++num_cmps;
		for(int j = i; j >= step && A[j] < A[j-step]; j -= step)
		{
			num_cmps += 2;
			temp = A[j];
			A[j] = A[j-step];
			A[j - step] = temp;
		}
		num_cmps += 2;
	}
	++num_cmps;
	step /= 2;
}
++num_cmps;
}

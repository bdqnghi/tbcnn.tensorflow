//============================================================================
// Name        : shell-sort.cpp
// Author      : Josh Zschiesche/Todd Christian
// Date        : Feb-12-2016
// Copyright   : http://mathbits.com/MathBits/CompSci/Arrays/Shell.htm and http://www.cplusplus.com/forum/general/123961/ and her lecture slides and the book
// Description : Implementation of shell sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

void
ShellSort::sort(int A[], int size)
{
	int diff = 0;
	int i = 0;
	int j = 0;
	int t = 0;
	
    for(diff = size/2; diff > 0; diff = diff/2)
	{
		++num_cmps;
        for(i = diff; i < size; ++i)
		{
            for(j = i - diff; j >= 0 && A[j] > A[j+diff]; j=j-diff) 
			{
				++num_cmps;
				++num_cmps;
                t = A[j];
                A[j] = A[j+diff];
                A[j+diff] = t;
            }
		}
	}
}
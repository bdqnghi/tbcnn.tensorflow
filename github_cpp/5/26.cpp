







#include "sort.h"

void
InsertionSort::sort(int A[], int size)				
{
	int i;
	int pos;
	int key;

    for(i = 1; i < size; ++i)
    {
		++num_cmps;
        key = A[i];
        for (pos = i - 1; pos >= 0 && A[pos] > key; --pos)
		{
			++num_cmps;
			++num_cmps;
            A[1+pos] = A[pos];
		}
        A[1+pos] = key;
    }
}
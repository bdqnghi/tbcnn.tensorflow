/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		SelectionSort.h
Date Created:	1/23/16
Modifications:

*****************************************************************************************/

#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include "SwapSort.h"

template<typename RT, typename T>
class SelectionSort : SwapSort<RT, T>
{ 
public:
	SelectionSort(RT & ra, int length);

	virtual void Sort(RT & ra, int length);
};

template<typename RT, typename T>
SelectionSort<RT, T>::SelectionSort(RT & ra, int length)
{
	Sort(ra, length);
}

template<typename RT, typename T>
void SelectionSort<RT, T>::Sort(RT & ra, int length)
{
	int least, i, j;
	for (i = 0; i < length - 1; ++i)
	{
		least = i;

		for (j = i + 1; j < length; ++j)
		{
			if (ra[j] < ra[least])
				least = j;
		}
	
		if(least > i)
			Swap(ra[i], ra[least]);
	}
}


#endif // SELECTIONSORT_H
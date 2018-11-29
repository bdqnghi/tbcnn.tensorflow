/*****************************************************************************************
Author:			Garrett Fleischer
Filename:		HeapSort.h
Date Created:	1/23/16
Modifications:

*****************************************************************************************/

#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "SwapSort.h"

template<typename RT, typename T>
class HeapSort : SwapSort <RT, T>
{
public:
	HeapSort(RT & ra, int length);

	virtual void Sort(RT & ra, int length);

private:
	void MoveDown(RT & ra, int first, int last);
};

template<typename RT, typename T>
HeapSort<RT, T>::HeapSort(RT & ra, int length)
{
	Sort(ra, length);
}

template<typename RT, typename T>
void HeapSort<RT, T>::Sort(RT & ra, int length)
{
	int last = length - 1,
		first = length / 2 - 1;

	while (first >= 0)
		MoveDown(ra, first--, last);

	for (int i = last; i >= 0; --i)
	{
		Swap(ra[0], ra[i]);
		MoveDown(ra, 0, i - 1);
	}
}


template<typename RT, typename T>
void HeapSort<RT, T>::MoveDown(RT & ra, int first, int last)
{
	int largest = first * 2 + 1;

	while (largest <= last)
	{
		if (largest < last && ra[largest] < ra[largest + 1])
			largest++;

		if (ra[first] < ra[largest])
		{
			Swap(ra[first], ra[largest]);
			first = largest;
			largest = first * 2 + 1;
		}
		else
			largest = last + 1;
	}
}

#endif // HEAPSORT_H

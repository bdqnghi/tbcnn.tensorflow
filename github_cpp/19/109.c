









#include "SortData.h"
#include "QuickSort.h"


QuickSort::QuickSort(int max)
	: SortData(max)
{
	
	
}


QuickSort::~QuickSort()
{
	
	
}


_int64 QuickSort::sort()
{
	
	numops = 0;

	
	quicksort(theData, maxSize);

	return numops;
}


void QuickSort::quicksort(long theArray[], int n)
{
	recQuickSort(theArray, 0, n - 1);
}

void QuickSort::recQuickSort(long theArray[], int first, int last)
{
	int pivotLoc;

	if (first < last)
	{
		pivotLoc = partition(theArray, first, last);
		recQuickSort(theArray, first, pivotLoc - 1);
		recQuickSort(theArray, pivotLoc + 1, last);
	}
}

void QuickSort::swap(long theArray[], int first, int second)
{
	long temp;

	temp = theArray[first];
	theArray[first] = theArray[second];
	theArray[second] = temp;
	numops += 3;
}

int QuickSort::partition(long theArray[], int first, int last)
{
	long pivot;

	int index;
	int smallIndex;

	swap(theArray, first, (first + last) / 2);

	pivot = theArray[first]; numops++;
	smallIndex = first;

	for (index = first + 1; index <= last; index++)
	{
		if ((++numops) && theArray[index] < pivot)
		{
			smallIndex++;
			swap(theArray, smallIndex, index);
		}
	}

	swap(theArray, first, smallIndex);

	return smallIndex;
}
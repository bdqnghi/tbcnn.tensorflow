









#include "SortData.h"
#include "InsertionSort.h"


InsertionSort::InsertionSort(int max)
	: SortData(max)
{
	
	
}


InsertionSort::~InsertionSort()
{
	
	
}


_int64 InsertionSort::sort()
{
	
	numops = 0;

	
	insertionsort(theData, maxSize);

	return numops;
}


void InsertionSort::insertionsort(long theArray[], int n)
{
	
	
	for (int firstOutOfOrder = 1; firstOutOfOrder < n; firstOutOfOrder++)
	{
		if ((++numops) && theArray[firstOutOfOrder] < theArray[firstOutOfOrder - 1])
		{
			long temp = theArray[firstOutOfOrder]; numops++;
			int loc = firstOutOfOrder;

			do
			{
				theArray[loc] = theArray[loc - 1]; numops++;
				loc--;
			}
			while ((++numops) && loc > 0 && theArray[loc - 1] > temp);

			theArray[loc] = temp; numops++;
		}
	}
}
/*******************************************************************
*   File: QuickSort.cpp											   *
*   Name: James Walker (Ethan)									   *
*   Project: Programming Assignment 4: Sorting					   *
*   Creation Date: 12/06/2013									   *
*   Purpose: CPP define Quick Sort	 							   *
*   															   *
*******************************************************************/

#include "QuickSort.h"

QuickSort::QuickSort()
{

}

QuickSort::~QuickSort()
{

}



void QuickSort::printName()
{
	std::cout << "\n--------------------------------------------------------" << std::endl;
	std::cout << "-----------------------QUICK SORT-----------------------" << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
}

void  QuickSort::sort()
{
	sort(0, (NUMRECS-1));
}

void  QuickSort::sort(int startIndex, int endIndex)
{


	int i, j;
	
	SortData temp;

    if(startIndex < endIndex)
    {
	
        i = startIndex;
        j = endIndex;
		partition(dataArray, &i, &j);
        sort(startIndex, j);
        sort(i, endIndex);
    }



}

void QuickSort::partition(SortData DataArray[], int *I, int *J)
{
	int         pivot;    
	SortData    temp;

	pivot = dataArray[(*I + *J) / 2].key; 
	do
	{
		
		while (dataArray[*I].key < pivot) (*I)++;
		while (dataArray[*J].key > pivot) (*J)--;

		
		if (*I <= *J)
		{
			temp = dataArray[*I];
			dataArray[*I] = dataArray[*J];
			dataArray[*J] = temp;
			(*I)++;            
			(*J)--;           
		}
	} while (*I <= *J);
	
}
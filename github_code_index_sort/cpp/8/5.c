#include <iostream>
#include <string>
#include "SortFunctions.h"
#include <utility>
/*
This .CPP file holds the following sorting functions:
SELECTION SORT
QUICK SORT
INSERTION SORT
*/
/*
SELECTION SORTING FUNCTION
*/
void SFunc::SelectionSort(int A[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int iMin = i; //ith position: elements from i till n-1 are candiates
		for (int j = i + 1; j < n; j++)
		{
			if (A[j] < A[iMin])
				iMin = j; // updates the index of minimum element
		}
		int temp = A[i];
		A[i] = A[iMin];
		A[iMin] = temp;
	}
	for (int k = 0; k < n; k++)
	{
		std::cout << A[k] << " ";
	}
}
/*
QUICK SORTING ALGORITHM FUNCTION 
*/
int Partition(int *A, int start, int end)
{
	int pivot = A[end];
	int partitionIndex = start; //set partition index as start initially
	for (int i = start; i < end; i++)
	{
		if (A[i] <= pivot)
		{
			std::swap(A[i], A[partitionIndex]); // swap if element is lesser than pivot
			partitionIndex++;
		}
	}
	std::swap(A[partitionIndex], A[end]);
	return partitionIndex;
}
void SFunc::QuickSort(int *A, int start, int end)
{
	if (start < end)
	{
		int partitionIndex = Partition(A, start, end); //calling Partition
		QuickSort(A, start, partitionIndex - 1);
		QuickSort(A, partitionIndex + 1, end);
	}
	/*for (int i = 0; i < end; i++)
	{
		std::cout << Partition << std::endl;
	}*/
	
}
/*
INSERTION SORT ALGORITHM FUNCTION
*/
void SFunc::InsertionSort(int arr[], int length)
{
	int j, temp;

	for (int i = 0; i < length; i++){
		j = i;

		while (j > 0 && arr[j] < arr[j - 1]){
			temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;
			j--;
		}
	}
	for (int k = 0; k < length; k++)
	{
		std::cout << arr[k] << " ";
	}
}

/*
For RADISX SORT PLEASE SEE RADIXSORT.CPP
For HEAP SORT PLEASE SEE HEAPSORT.CPP
*/

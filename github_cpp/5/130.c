


#include "stdafx.h"
#include "InsertionSort_Cpp.h"

void _stdcall insertionSort(int* arrayToSort, int arraySize)
{
	int keyValue, counter;
	for (int i = 1; i < arraySize; i++)
	{
		keyValue = arrayToSort[i];
		for (counter = i - 1; counter >= 0 && arrayToSort[counter] > keyValue; counter--)
		{
			arrayToSort[counter + 1] = arrayToSort[counter];
		}
		arrayToSort[counter + 1] = keyValue;
	}
}


bool _stdcall checkIfSorted(int arraySize, int* sortedArray)
{
	for (int i = 0; i < arraySize - 1; i++)
	{
		if (sortedArray[i] > sortedArray[i + 1])
			return false;
	}
	return true;
}
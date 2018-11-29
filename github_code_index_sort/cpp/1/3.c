#include "InsertionSort.h"

InsertionSort::InsertionSort() : arraySize(0), insertionArray(NULL)
{
}

InsertionSort::~InsertionSort()
{
	if (insertionArray != NULL)
		delete[] insertionArray;
}

void InsertionSort::SortAscending()
{
	Sort(true);
}

void InsertionSort::SortDescending()
{
	Sort(false);

}

void InsertionSort::Sort(bool Ascend)
{
	for (int i = 1; i < arraySize; i++)
	{
		int j;
		int compData = insertionArray[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (Ascend)
			{
				if (insertionArray[j] > compData)
				{
					insertionArray[j + 1] = insertionArray[j];
				}
				else
					break;
			}
			else
			{
				if (insertionArray[j] < compData)
				{
					insertionArray[j + 1] = insertionArray[j];
				}
				else
					break;
			}
		}
		if (j < i - 1)
			insertionArray[j + 1] = compData;
	}
}

void InsertionSort::SetArray(const int *arr, size_t len)
{
	if (insertionArray != NULL)
		delete[] insertionArray;

	insertionArray = new int[len];
	arraySize = len;

	memcpy(insertionArray, arr, sizeof(int) * len);
}

void InsertionSort::TestAllSort() const
{
	for (int i = 0; i < arraySize; i++)
	{
		std::cout << insertionArray[i] << " ";
	}
	std::cout << std::endl;
}
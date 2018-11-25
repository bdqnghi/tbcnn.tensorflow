#include "stdafx.h"
#include "BubbleSort.h"


BubbleSort::BubbleSort()
{
}

void BubbleSort::swap(int *xp, int *yp)
{
	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void BubbleSort::bubbleSort(int *arr, int elemNumber)
{
	for (i = 0; i < elemNumber - 1; i++)
	{
		swapped = false;
		for (j = 0; j < elemNumber - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
		break;
	}
}

void BubbleSort::PrintData(int *arr, int size)
{
	for (i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}


BubbleSort::~BubbleSort()
{
}



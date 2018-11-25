
#include "SelectionSort.h"



SelectionSort::SelectionSort() : arraySize(0), selectionArray(NULL)
{
}


SelectionSort::~SelectionSort()
{
	if (selectionArray != NULL)
		delete[] selectionArray;
}

void SelectionSort::SortAscending()
{
	Sort(true);
}

void SelectionSort::SortDescending()
{
	Sort(false);
}

void SelectionSort::Sort(bool Ascend)
{
	for (int i = 0; i < arraySize - 1; i++)
	{
		int targetIdx = i;

		if (Ascend)
		{
			for (int comp = i + 1; comp < arraySize; comp++)
			{
				if (selectionArray[targetIdx] > selectionArray[comp])
					targetIdx = comp;
			}
		}
		else
		{
			for (int comp = i + 1; comp < arraySize; comp++)
			{
				if (selectionArray[targetIdx] < selectionArray[comp])
					targetIdx = comp;
			}
		}

		if (targetIdx != i)
		{
			int temp = selectionArray[i];
			selectionArray[i] = selectionArray[targetIdx];
			selectionArray[targetIdx] = temp;
		}
	}
}

void SelectionSort::SetArray(const int *arr, size_t len)
{
	if (selectionArray != NULL)
		delete[] selectionArray;

	selectionArray = new int[len];
	arraySize = len;

	memcpy(selectionArray, arr, sizeof(int) * len);
}

void SelectionSort::TestAllSort() const
{
	for (int i = 0; i < arraySize; i++)
	{
		std::cout << selectionArray[i] << " ";
	}
	std::cout << std::endl;
}

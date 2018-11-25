#include "stdafx.h"
#include "BubbleSort.h"

int main1()
{
	std::vector<int> data = { 9, 1, 8, 2, 7, 3, 6, 4, 5 };
	BubbleSort *bs = new BubbleSort(data);
	bs->sort2();
	for (int i = 0; i < data.size(); i++)
	{
		std::cout << data[i] << " ";
	}
	return 0;
}

BubbleSort::BubbleSort(std::vector<int> &data): 
	arr(data)
{
}

bool BubbleSort::less(int value1, int value2)
{
	return value1 < value2;
}

bool BubbleSort::more(int value1, int value2)
{
	return value1 > value2;
}

void BubbleSort::sort()
{
	int size = arr.size();

	int i, j, temp;
	for (i = 0; i < (size - 1); i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (more(arr[j], arr[j + 1]))
			{
				
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void BubbleSort::sort2()
{
	int size = arr.size();
	int i, j, temp, swapped = 1;
	for (i = 0; i < (size - 1) && swapped == 1; i++)
	{
		swapped = 0;
		for (j = 0; j < size - i - 1; j++)
		{
			if (more(arr[j], arr[j + 1]))
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
		}
	}
}
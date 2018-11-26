#include "BubbleSort.h"

using namespace std;

BubbleSort::BubbleSort() : bubbleArray(NULL), arraySize(0)
{
}

BubbleSort::~BubbleSort()
{
	if (bubbleArray != NULL)
		delete[] bubbleArray;
}

void BubbleSort::SortAscending()
{
	Sort(true);
}

void BubbleSort::SortDescending()
{
	Sort(false);
}

void BubbleSort::Sort(bool ascend)
{
	for (int i = 0; i < arraySize - 1; i++)
	{
		bool swapCheck = false;
		for (int comp = 0; comp < (arraySize - 1) - i; comp++)
		{
			if (ascend)
			{
				if (bubbleArray[comp] > bubbleArray[comp + 1])
				{
					int temp = bubbleArray[comp + 1];
					bubbleArray[comp + 1] = bubbleArray[comp];
					bubbleArray[comp] = temp;
					swapCheck = true;
				}
			}
			else
			{
				if (bubbleArray[comp] < bubbleArray[comp + 1])
				{
					int temp = bubbleArray[comp + 1];
					bubbleArray[comp + 1] = bubbleArray[comp];
					bubbleArray[comp] = temp;
					swapCheck = true;
				}
			}
		}
		if (swapCheck == false)
			break;
	}
}

void BubbleSort::SetArray(const int *arr, size_t len)
{
	if (bubbleArray != NULL)
		delete[] bubbleArray;

	bubbleArray = new int[len];
	arraySize = len;
	
	memcpy(bubbleArray, arr, (sizeof(int) * len));
}

void BubbleSort::TestAllSort() const
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << bubbleArray[i] << " ";
	}
	cout << endl;
}

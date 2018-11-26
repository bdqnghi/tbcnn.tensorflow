#include "SortAlgorithms.h"
#include "AlgorithmTest.h"

void swap(int& a, int& b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

int* BubbleSort(int* a_Input, int a_size)
{
	assert(a_Input != nullptr && a_size != 0);

	{
		lock_guard<mutex> printLock(g_PrintMutex);
		printf("Start bubble sorting list:  ");
		AlgorithmTest::PrintIntList(a_Input, a_size);
		printf("... \n");
	}

	int numComp = 0;
	int numSwap = 0;

	bool finished = false;
	while (!finished)
	{
		finished = true;
		for (int i = 1; i < a_size; i++)
		{
			numComp++;
			if (a_Input[i - 1] > a_Input[i])
			{
				swap(a_Input[i - 1], a_Input[i]);
				numSwap++;
				finished = false;
			}
		}
	}

	{
		lock_guard<mutex> printLock(g_PrintMutex);
		printf("BubbleSort Complete : numberComparison:%i numberSwap:%i \n", numComp, numSwap);
	}
	return a_Input;
}

int* SelectionSort(int* a_Input, int a_size)
{
	assert(a_Input != nullptr && a_size != 0);

	{
		lock_guard<mutex> printLock(g_PrintMutex);
		printf("Start SelectionSort list:  ");
		AlgorithmTest::PrintIntList(a_Input, a_size);
		printf("... \n");
	}

	int numComp = 0;
	int numSwap = 0;

	for (int i = 0; i < a_size; i++)
	{
		int imin = i;
		for (int j = i + 1; j < a_size; j++)
		{
			numComp++;
			if (a_Input[j] < a_Input[imin])
			{
				imin = j;
			}
		}
		if (imin != i)
		{
			swap(a_Input[i], a_Input[imin]);
			numSwap++;
		}
	}

	{
		lock_guard<mutex> printLock(g_PrintMutex);
		printf("SelectionSort Complete : numberComparison:%i numberSwap:%i \n", numComp, numSwap);
	}
	return a_Input;
}

int* QuickSort(int* a_Input, int a_size)
{
	assert(a_Input != nullptr && a_size != 0);

	{
		lock_guard<mutex> printLock(g_PrintMutex);
		printf("Start QuickSort list:  ");
		AlgorithmTest::PrintIntList(a_Input, a_size);
		printf("... \n");
	}

	int numCompQuickSort = 0;
	int numSwapQuickSort = 0;

	QuickSort(a_Input, 0, a_size - 1, numCompQuickSort, numSwapQuickSort);

	{
		lock_guard<mutex> printLock(g_PrintMutex);
		printf("QuickSort Complete : numberComparison:%i numberSwap:%i \n", numCompQuickSort, numSwapQuickSort);
	}
	return a_Input;
}

int* QuickSort(int* a_arr, int a_left, int a_right, int& o_numCompQuickSort, int& o_numSwapQuickSort) {
	int i = a_left, j = a_right;
	int tmp;
	int pivot = a_arr[(a_left + a_right) / 2];

	/* partition */
	while (i <= j) {
		while (a_arr[i] < pivot)
		{
			o_numCompQuickSort++;
			i++;
		}
		while (a_arr[j] > pivot)
		{
			o_numCompQuickSort++;
			j--;
		}
		if (i <= j) {
			o_numSwapQuickSort++;
			tmp = a_arr[i];
			a_arr[i] = a_arr[j];
			a_arr[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (a_left < j)
		QuickSort(a_arr, a_left, j, o_numCompQuickSort, o_numSwapQuickSort);
	if (i < a_right)
		QuickSort(a_arr, i, a_right,o_numCompQuickSort, o_numSwapQuickSort);

	return a_arr;
}

void SortVector(vector<int>& a_nums)
{
	bool finished = false;
	while (!finished)
	{
		finished = true;
		for (int i = 1; i < a_nums.size(); i++)
		{
			if (a_nums[i - 1] > a_nums[i])
			{
				swap(a_nums[i - 1], a_nums[i]);
				finished = false;
			}
		}
	}

}


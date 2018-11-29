#include "QuickSort.h"

QuickSort::QuickSort()
	:SwapCount(0)
{
}


QuickSort::~QuickSort()
{
}

void QuickSort::OnInit()
{
	/*, 70, 40, 80, 60, 20, 15, 25, 55, 85, 45, 75, 65, 16, 86, 56, 36, 46, 96, 26*/
	int a[] = { 50, 10, 90, 30 , 70, 40, 80, 60 };
	aLen = sizeof(a) / sizeof(int);
	quickSort(a, 0, aLen - 1);
	/*cout << "ArrLen" << aLen << " QuickSortSwapCount" << SwapCount << "\n";*/
}

int QuickSort::Partition(int a[], int low, int high)
{
	midOptimize(a, low, high);
	int pivotKey = a[low];
	while (low < high)
	{
		while (low < high && a[high] >= pivotKey)
		{
			high--;
		}
		Swap(a, low, high);
		Pirnt(a, aLen);
		while (low < high && a[low] <= pivotKey)
		{
			low++;
		}
		Swap(a, low, high);
		Pirnt(a, aLen);
	}
	return low;
}

void QuickSort::quickSort(int a[], int low, int high)
{
	if (low < high)
	{
		int q = Partition(a, low, high);
		quickSort(a, low, q - 1);
		quickSort(a, q + 1, high);
	}
}

void QuickSort::Pirnt(int a[], int len)
{
	//return;
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << " ";
	}
	cout << "\n";
}

void QuickSort::Swap(int a[], int s, int m)
{
	int temp = a[m];
	a[m] = a[s];
	a[s] = temp;
	SwapCount++;
}

//����low λ�ñ���м�����
void QuickSort::midOptimize(int a[], int low, int high)
{
	int m = low + (high - low) / 2;
	if (a[low] > a[high])
		Swap(a, low, high);
	if (a[m] > a[high])
		Swap(a, low, high);
	if (a[m] > a[low])
		Swap(a, m, low);
}


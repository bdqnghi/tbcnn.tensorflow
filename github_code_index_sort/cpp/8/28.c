#include "QuickSort.h"


// ----------------------------------
// Constructor and destructor

QuickSort::QuickSort() : arraySize(0), quickArray(NULL)
{
}


QuickSort::~QuickSort()
{
	if (quickArray != NULL)
		delete[] quickArray;
}


// ----------------------------------
// Public methods

void QuickSort::SetArray(const int * arr, size_t len)
{
	if (quickArray != NULL)
		delete[] quickArray;
	quickArray = new int[len];
	arraySize = len;

	memcpy(quickArray, arr, sizeof(int) * len);
}

void QuickSort::ResetArray()
{
	if (quickArray != NULL)
	{
		delete[] quickArray;
		quickArray = NULL;
		arraySize = 0;
	}
}

const int * QuickSort::GetArray() const
{
	return quickArray;
}

size_t QuickSort::GetArraySize() const
{
	return arraySize;
}

void QuickSort::Sort(int left, int right)
{
	if (left < right)
	{
		int pivotIdx = Partition(left, right);
		Sort(left, pivotIdx - 1);
		Sort(pivotIdx + 1, right);
	}
}

void QuickSort::TestAllArray() const
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << quickArray[i] << " ";
	}
	cout << endl;
}

// ----------------------------------
// Private methods

void QuickSort::Swap(int idx1, int idx2)
{
	if (idx1 != idx2)
	{
		int temp = quickArray[idx1];
		quickArray[idx1] = quickArray[idx2];
		quickArray[idx2] = temp;
	}
}

int QuickSort::Partition(int left, int right)
{
	int pivotVal = quickArray[left]; // ũ�� �񱳸� �� ������
	int low = left + 1; // ���ʿ��� �Ǻ����� ū ���� ã�� �ε���
	int high = right; // �����ʿ��� �Ǻ����� ���� ���� ã�� �ε���

	while (low <= high)
	{
		while (pivotVal >= quickArray[low] && low <= right)
			low++;

		while (pivotVal <= quickArray[high] && high >= (left + 1))
			high--;

		if (low < high)
			Swap(low, high);
	}
	Swap(left, high);
	return high;
}

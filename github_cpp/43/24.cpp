#include "list.h"

void bucket_sort(double* A, int length)
{
	// extra bucket for A[i] = 1.000
	List *bucket = new List[length + 1];
	for (int i = 0; i < length; i++)
		bucket[int(A[i] * length)].insert(A[i]);
	for (int i = 0; i < length + 1; i++)
		bucket[i].sort();
	int last_index = 0;
	for (int i = 0; i < length + 1; i++)
	{
		std::copy(bucket[i]._list_data, bucket[i]._list_data + bucket[i].size(), A + last_index);
		last_index += bucket[i].size();
	}
}

void insert_sort(double* A, int length)
{
	int j = 0; double tmp = 0.;
	for (int i = 0; i < length; i++)
	{
		j = i - 1;
		tmp = A[i];
		while ((j >= 0) && (A[j] > tmp))
		{
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = tmp;
	}
}

bool test_sort(double* A, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		if (A[i] > A[i + 1])
		{
			std::cout << "Wrong at " << i << std::endl;
			return false;
		}
	}
	return true;
}

void quick_sort(double* A, int low, int high)
{
	int partition(double* A, int low, int high);
	void insert_sort(double* A, int length);
	if (high - low + 1 <= 50)
		insert_sort(A + low, high - low + 1);
	else
	{
		int mid = partition(A, low, high);
		if (mid - 1 > low)
			quick_sort(A, low, mid - 1);
		if (high > mid + 1)
			quick_sort(A, mid + 1, high);
	}
}

int partition(double* A, int low, int high)
{
	double x = A[high], tmp = 0;
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (A[j] <= x)
		{
			i++;
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
	}
	tmp = A[i + 1];
	A[i + 1] = A[high];
	A[high] = tmp;
	return i + 1;
}
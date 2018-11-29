#include <iostream>

using namespace std;

bool MergeSort(int a[], int n);
void mergesort(int a[], int first, int last, int temp[]);
void mergearray(int a[], int first, int mid, int last, int temp[]);

int main()
{
	int i = 0, temp = 0;
	int a[10] = {0};
	for (i = 0; i < 10; i++)
	{
		cin >> a[i];
	}
	MergeSort(a, 10);
	for (i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}

bool MergeSort(int a[], int n)
{
	int *p = new int[n];
	if (p == NULL)
		return false;
	mergesort(a, 0, n - 1, p);
	delete[] p;
	return true;
}

void mergesort(int a[], int first, int last, int temp[])
{
	if (first < last)
	{
		int mid = (first + last) / 2;
		mergesort(a, first, mid, temp); //��������
		mergesort(a, mid + 1, last, temp);//������ұ�
		mergearray(a, first, mid, last, temp);//�������������кϲ�
	}
}

void mergearray(int a[], int first, int mid, int last, int temp[])
{
	int i = first, j = mid + 1;
	int m = mid, n = last;
	int k = 0;

	while (i <= m && j <= n)
	{
		if (a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}

	while (i <= m)
		temp[k++] = a[i++];

	while (j <= n)
		temp[k++] = a[j++];

	for (i = 0; i < k; i++)
		a[first + i] = temp[i];
}
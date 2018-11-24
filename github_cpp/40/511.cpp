#include <iostream>

using namespace std;

int partition(int *a, int low, int high)
{
	int i = low - 1;
	int j = low;
	int pivot = a[high];
	int tmp;
	while(j < high) {
		if (a[j] <= pivot) {
			i ++;
		  tmp = a[i];
		 	a[i] = a[j];
		  a[j] = tmp;	
		}
		j ++;
	}
	i++;
	tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
	return i;
}

void quickSort(int * a, int low, int high)
{
	if (low < high) {
		int i = partition(a, low, high);
		quickSort(a, low, i - 1);
		quickSort(a, i + 1, high);
	}
}

void printArr(int * a, int len)
{
	for (int i = 0; i < len; ++i) {
		cout << a[i] << "\t";
	}
}

int main(void) {
	int a[] = {2, 10, 18, 7, 6, 49, 38, 65, 97, 76, 13, 27};
	int len = sizeof(a) / sizeof(a[0]);
	cout << "Before Sorting: ";
	printArr(a, len);
	cout << "\nAfter sorting: ";
	quickSort(a, 0, len - 1);
	printArr(a, len);
	return 0;
}

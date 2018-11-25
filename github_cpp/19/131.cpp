


#include "pch.h"
#include <iostream>
void sort(int a[], int lo, int hi);
int partition(int a[], int lo, int hi);
int main()
{
	using namespace std;
	int test[] = { 56,91,30,17,25,19,38,65,23,1,9,6,34,58,2,3,59,751,0,197,36,48,76,69 };
	
	int j = partition(test, 0, 23);
	
	
	
	sort(test, 0, j - 1);
	
	
	
	sort(test, j + 1, 23);
	for (int i = 0; i < 24; i++) {
	cout << test[i] << " ";
    }
	return 0;
}

void sort(int a[], int lo, int hi) {
	int min, temp;
	for (int i = lo; i < hi + 1; i++) {
		min = i;
		for (int j = i + 1; j < hi + 1; j++) {
			if (a[j] < a[min]) {
				min = j;
			}
		}
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
}

int partition(int a[], int lo, int hi) {
	int i = lo, j = hi + 1;
	int temp = a[lo];
	while (true) {
		while (a[++i] < temp) if (i == hi) break;
		while (temp < a[--j]) if (j == lo) break;
		if (i >= j) break;
		int as = a[i];
		a[i] = a[j];
		a[j] = as;
	}
	int as = a[lo];
	a[lo] = a[j];
	a[j] = as;
	return j;
}
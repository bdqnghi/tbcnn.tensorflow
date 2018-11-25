











#include "stdafx.h"
#include <iostream>


using namespace std;



void print_ar(int ar[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		cout << ar[i] << " ";
	}
	cout << endl;
}


void shell_sort(int ar[], int size)
{
	int j;

	
	for (int gap = size / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < size; ++i)
		{
			int temp = ar[i];
			for (j = i; j >= gap && temp < ar[j - gap]; j -= gap)
			{
				ar[j] = ar[j - gap];
			}
			ar[j] = temp;
		}
	}
}


int main(int argc, const char * argv[]) {

	
	int ar[] = { 1, 4, 16, 30, 29, 18, 100, 2, 43, 1 };

	
	cout << "Intial Array : ";
	print_ar(ar, 10);

	
	shell_sort(ar, 10);

	
	cout << "Sorted Array : ";
	print_ar(ar, 10);

	return 0;
}




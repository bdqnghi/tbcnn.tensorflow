#include "SelectionSort.h"



void SelectionSort::thread1()
{
	int temp, minimum;
	for (int i = 0; i<n/4 - 1; i++)
	{
		minimum = i;
		for (int j = i + 1; j<n/4; j++)
		{
			if (arrayy[j] < arrayy[minimum])
				minimum = j;
		}
		temp = arrayy[i];
		arrayy[i] = arrayy[minimum];
		arrayy[minimum] = temp;
	}
}

void SelectionSort::thread2()
{
	int temp, minimum;
	for (int i =n/4; i<n / 2 - 1; i++)
	{
		minimum = i;
		for (int j = i + 1; j<n / 2; j++)
		{
			if (arrayy[j] < arrayy[minimum])
				minimum = j;
		}
		temp = arrayy[i];
		arrayy[i] = arrayy[minimum];
		arrayy[minimum] = temp;
	}
}

void SelectionSort::thread3()
{
	int temp, minimum;
	for (int i = n / 2; i<n /4*3 - 1; i++)
	{
		minimum = i;
		for (int j = i + 1; j<n /4*3; j++)
		{
			if (arrayy[j] < arrayy[minimum])
				minimum = j;
		}
		temp = arrayy[i];
		arrayy[i] = arrayy[minimum];
		arrayy[minimum] = temp;
	}
}

void SelectionSort::thread4()
{
	int temp, minimum;
	for (int i = n /4*3; i<n - 1; i++)
	{
		minimum = i;
		for (int j = i + 1; j<n; j++)
		{
			if (arrayy[j] < arrayy[minimum])
				minimum = j;
		}
		temp = arrayy[i];
		arrayy[i] = arrayy[minimum];
		arrayy[minimum] = temp;
	}
}

SelectionSort::SelectionSort()
{
}


SelectionSort::~SelectionSort()
{
}
const SelectionSort & SelectionSort::operator=(const BubbleSort & copyArray)
{
	this->n = copyArray.n;
	arrayy = new int[n];
	for (int i = 0; i < n; i++) {
		arrayy[i] = copyArray.Original[i];
	}
	return *this;
}
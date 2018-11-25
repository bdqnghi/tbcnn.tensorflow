#include "InsertionSort.h"



InsertionSort::InsertionSort()
{
	
}

void InsertionSort::thread1()
{
	int temp, j;
	for (int i = 0; i < n / 4; i++) {
		j = i;
		while (j > 0 && arrayy[j] < arrayy[j - 1]) {
			temp = arrayy[j];
			arrayy[j] = arrayy[j - 1];
			arrayy[j - 1] = temp;
			j--;
		}
	}
}

void InsertionSort::thread2()
{

	int temp, j;
	for (int i = n/4; i < n / 2; i++) {
		j = i;
		while (j > n/4 && arrayy[j] < arrayy[j - 1]) {
			temp = arrayy[j];
			arrayy[j] = arrayy[j - 1];
			arrayy[j - 1] = temp;
			j--;
		}
	}
}

void InsertionSort::thread3()
{
	int temp, j;
	for (int i = n / 2; i < n /4*3; i++) {
		j = i;
		while (j > n/2 && arrayy[j] < arrayy[j - 1]) {
			temp = arrayy[j];
			arrayy[j] = arrayy[j - 1];
			arrayy[j - 1] = temp;
			j--;
		}
	}
}

void InsertionSort::thread4()
{
	int temp, j;
	for (int i = n / 4*3; i < n ; i++) {
		j = i;
		while (j > n/4*3 && arrayy[j] < arrayy[j - 1]) {
			temp = arrayy[j];
			arrayy[j] = arrayy[j - 1];
			arrayy[j - 1] = temp;
			j--;
		}
	}
}

const InsertionSort & InsertionSort::operator=(const BubbleSort & copyArray)
{
	this->n = copyArray.n;
	arrayy = new int[n];
	for (int i = 0; i < n; i++) {
		arrayy[i] = copyArray.Original[i];
	}
	return *this;
}
InsertionSort::~InsertionSort()
{
}

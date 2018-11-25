#include "stdafx.h"
#include "ShellSort.h"
#include <iostream>
#include "math.h"
#include "InsertionSort.h"

using namespace std;



ShellSort::ShellSort() {}


ShellSort::ShellSort(int *arr, int size)
{
	_size = size;
	wArray = arr;
	sort_it();
}

ShellSort::~ShellSort() 
{
	delete wArray;
}

int* ShellSort::get_array() { return wArray; }

void ShellSort::swap(int *first, int *second)
{
	int temp = *first;
	*first = *second;
	*second = temp;
}

void ShellSort::print_array()
{
	for (int i = 0; i < _size; i++)
	{
		cout << wArray[i] << ", ";
	}
}

void ShellSort::sort_it()
{
	continue_sorting(find_largest_gap(_size));
	InsertionSort sort(wArray, _size);
	wArray = sort.get_array();
}

void ShellSort::continue_sorting(int gap_size)
{
	if (gap_size < 3) {
		InsertionSort sort(wArray, _size);
		wArray = sort.get_array();
		return;
	}
	int left = 0;
	int right = gap_size;
	while (right < _size - 1)
	{
		if (wArray[left] > wArray[right])
			swap(&wArray[left], &wArray[right]);
		left = gap_size + 1;
		right += gap_size + 1;
	}
	kVal--;
	continue_sorting((int)pow(2,kVal) - 1);
}


int ShellSort::find_largest_gap(int array_length)
{
	kVal = 0; 
	int largest_gap_size = 0;

	while (largest_gap_size < array_length)
	{
		if (pow(2, kVal) - 1 >  array_length) {
			kVal--;
			break;
		}
		largest_gap_size = ((int)pow(2, kVal)) - 1;
		kVal++;
	}
	return largest_gap_size;
}
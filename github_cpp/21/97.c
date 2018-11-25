

#include <iostream>
#include "SelectionSort.h"

using namespace std;



SelectionSort::SelectionSort() {

	SelectionSort::CLASS_NAME = "SelectionSort";

	arr = 0;
	size = 0;

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}



SelectionSort::SelectionSort(int * a, int arrSize) {

	SelectionSort::CLASS_NAME = "SelectionSort";

	init(a, arrSize);

}



SelectionSort::~SelectionSort() {

	delete [] arr;
	size = 0;

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}



void SelectionSort::init(int * a, int arrSize) {

	size = arrSize;
	arr = new int [size];

	
	for (int i = 0; i < arrSize; i++)
		arr[i] = a[i];

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}



void SelectionSort::sort() {

	int min;

	
	for (int i = 0; i < size; i++) {

		min = i;

		
		for (int j = i; j < size; j++) {

			
			if (arr[j] < arr[min])
				min = j;

			numInnerLoops++;

		}

		
		if (i != min)
			swap(i, min);

		numOuterLoops++;

	}

}


void SelectionSort::sort(int * a, int arrSize) {

	
	init(a, arrSize);

	sort();

}



void SelectionSort::swap(int val1, int val2) {

	int temp;
	temp = arr[val2];
	arr[val2] = arr[val1];
	arr[val1] = temp;

	numSwaps++;

}



void SelectionSort::print() const {

	for (int i = 0; i < size; i++)
		cout << arr[i] << "\t";

	cout << endl;

}



int SelectionSort::getNumLoops() const {

	return (numInnerLoops + numOuterLoops);

}


int SelectionSort::getNumOuterLoops() const {

	return numOuterLoops;

}



int SelectionSort::getNumInnerLoops() const {

	return numInnerLoops;

}



int SelectionSort::getNumSwaps() const {

	return numSwaps;

}



int * SelectionSort::getArr() const {

	int * tmp = new int [size];

	for (int i = 0; i < size; i++)
		tmp[i] = arr[i];

	return tmp;

}
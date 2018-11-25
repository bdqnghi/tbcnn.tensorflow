

#include <iostream>
#include "BubbleSort.h"

using namespace std;



BubbleSort::BubbleSort() {

	BubbleSort::CLASS_NAME = "BubbleSort";

	arr = 0;
	size = 0;

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}



BubbleSort::BubbleSort(int * a, int arrSize) {

	BubbleSort::CLASS_NAME = "BubbleSort";

	init(a, arrSize);

}



BubbleSort::~BubbleSort() {

	delete [] arr;
	size = 0;

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}



void BubbleSort::init(int * a, int arrSize) {

	size = arrSize;
	arr = new int [size];

	
	for (int i = 0; i < arrSize; i++)
		arr[i] = a[i];

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}



void BubbleSort::sort() {

	bool flag = true;
	int i = size - 1;
	int count = 0;

	
	while (flag) {

		flag = false;

		
		for (i; i >= count; i--) {

			
			if (arr[i] < arr[i - 1]) {

				swap(i, i-1);
				numSwaps++;

				flag = true;

			}

			numInnerLoops++;

		}

		i = size - 1;
		count++;
		numOuterLoops++;

	}

}


void BubbleSort::sort(int * a, int arrSize) {

	init(a, arrSize);

	sort();

}



void BubbleSort::swap(int val1, int val2) {

	int temp;
	temp = arr[val2];
	arr[val2] = arr[val1];
	arr[val1] = temp;

}



void BubbleSort::print() const {

	for (int i = 0; i < size; i++)
		cout << arr[i] << "\t";

	cout << endl;

}




int BubbleSort::getNumLoops() const {

	return (numInnerLoops + numOuterLoops);

}



int BubbleSort::getNumOuterLoops() const {

	return numOuterLoops;

}



int BubbleSort::getNumInnerLoops() const {

	return numInnerLoops;

}



int BubbleSort::getNumSwaps() const {

	return numSwaps;

}



int * BubbleSort::getArr() const {

	int * tmp = new int [size];

	for (int i = 0; i < size; i++)
		tmp[i] = arr[i];

	return tmp;

}


#include <iostream>
#include "InsertionSort.h"

using namespace std;


void InsertionSort::swap(int val1, int val2) {

	int temp;
	temp = arr[val2];
	arr[val2] = arr[val1];
	arr[val1] = temp;
	numSwaps++;

}



void InsertionSort::init(int * a, int arrSize) {

	size = arrSize;
	arr = new int [size];

	
	for (int i = 0; i < arrSize; i++)
		arr[i] = a[i];

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;


}



InsertionSort::InsertionSort() {

	InsertionSort::CLASS_NAME = "InsertionSort";
	
	arr = 0;
	size = 0;

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}



InsertionSort::InsertionSort(int * a, int arrSize) {

	InsertionSort::CLASS_NAME = "InsertionSort";

	init(a, arrSize);

}



InsertionSort::~InsertionSort() {

	delete [] arr;
	size = 0;

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;


}



void InsertionSort::sort() {

	
	for (int position = 0; position < size; ++position) {
		
		
		while ((position > 0) && (arr[position-1] > arr[position])) {

			
			swap(position, position-1);
			--position;
			numInnerLoops++;

        }

		numOuterLoops++;

    }

}



void InsertionSort::sort(int * a, int arrSize) {

	init(a, arrSize);
	sort();

}



void InsertionSort::print() const {

	
	for (int i = 0; i < size; i++)
		cout << arr[i] << "\t";

	cout << endl;

}



int InsertionSort::getNumLoops() const {

	return (numInnerLoops + numOuterLoops);

}



int InsertionSort::getNumOuterLoops() const {

	return numOuterLoops;

}



int InsertionSort::getNumInnerLoops() const {

	return numInnerLoops;

}



int InsertionSort::getNumSwaps() const {

	return numSwaps;
}



int* InsertionSort::getArr() const {
	
	int * tmp = new int [size];

	for (int i = 0; i < size; i++)
		tmp[i] = arr[i];

	return tmp;

}
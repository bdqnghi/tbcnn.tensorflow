//
//  SelectionSort.cpp
//  Sorts integers using the SelectionSort algorithm


#include "SelectionSort.h"

using namespace std;

SelectionSort::SelectionSort() { // constructor
	sortArray.length = 0;
	sortArray.arr = NULL;
}

SelectionSort::~SelectionSort(){
	delete []sortArray.arr;
}
// reads in a list of integers from stdin and returns an arrayWithLength
void SelectionSort::readList() {
	int currentCapacity = 10;
	sortArray.arr = new int[currentCapacity];

	while (cin >> sortArray.arr[sortArray.length]) {
		++sortArray.length;
		if (sortArray.length == currentCapacity) {
			int *temp = new int[currentCapacity * 2];
			for (int i = 0; i < currentCapacity; i++) {
				temp[i] = sortArray.arr[i];
			}
			delete[] sortArray.arr;
			sortArray.arr = temp;
			currentCapacity *= 2;
		}
	}
}

void SelectionSort::sort() {
	// selection sort on sortArray
	for (int i = 0; i < sortArray.length; i++) {
		int minIndex = i;
		//find the position of the lowest one of the unsorted part
		for (int j = i + 1; j < sortArray.length; j++) {
			if (sortArray.arr[j] < sortArray.arr[minIndex])
				minIndex = j;
		}
		//swaps first element of unsorted part with minimal element
		//then it is included to the sorted part
		if(minIndex!=i){
			int tmp=sortArray.arr[i];
			sortArray.arr[i]=sortArray.arr[minIndex];
			sortArray.arr[minIndex]=tmp;
		}
	}
}
/*
 * print out intergers using for loop on separate lines
 */
void SelectionSort::printArray() {
	// prints out the integers in sorted order
	for (int i = 0; i < sortArray.length; i++){
		cout<< sortArray.arr[i]<<"\n";
	}
}







#include "SelectionSort.h"

using namespace std;

SelectionSort::SelectionSort() { 
	sortArray.length = 0;
	sortArray.arr = NULL;
}

SelectionSort::~SelectionSort(){
	delete []sortArray.arr;
}

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
	
	for (int i = 0; i < sortArray.length; i++) {
		int minIndex = i;
		
		for (int j = i + 1; j < sortArray.length; j++) {
			if (sortArray.arr[j] < sortArray.arr[minIndex])
				minIndex = j;
		}
		
		
		if(minIndex!=i){
			int tmp=sortArray.arr[i];
			sortArray.arr[i]=sortArray.arr[minIndex];
			sortArray.arr[minIndex]=tmp;
		}
	}
}

void SelectionSort::printArray() {
	
	for (int i = 0; i < sortArray.length; i++){
		cout<< sortArray.arr[i]<<"\n";
	}
}


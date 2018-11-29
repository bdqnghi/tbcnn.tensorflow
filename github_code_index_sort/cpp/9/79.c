//
//  SelectionSort.cpp
//  Sorts integers using the SelectionSort algorithm


#include "SelectionSort.h"

using namespace std;

SelectionSort::SelectionSort(){ // constructor
        sortArray.length = 0;
        sortArray.arr = NULL;
}

SelectionSort::~SelectionSort() {
    delete [] sortArray.arr;

}

// reads in a list of integers from stdin and returns an arrayWithLength
void SelectionSort::readList(){
        int currentCapacity = 10;
        sortArray.arr = new int[currentCapacity];
        
        while (cin >> sortArray.arr[sortArray.length]) {
                ++sortArray.length;
                if (sortArray.length==currentCapacity) {
                        int *temp = new int[currentCapacity*2];
                        for (int i=0;i<currentCapacity;i++) {
                                temp[i] = sortArray.arr[i];
                        }
                        delete [] sortArray.arr;
                        sortArray.arr = temp;
                        currentCapacity *= 2;
                }
        }
}

void SelectionSort::sort(){
    // selection sort on sortArray
    int min = sortArray.arr[0];
    int curr = 0;

    //nested loop to find minimum, iterates through list setting
    //each new min to the next open space in the array
    for(int j = 0; j < sortArray.length; j++) {
	min = sortArray.arr[j];
	for(int i = j; i< sortArray.length; i++) {
	    if (min > sortArray.arr[i]) {
		min = sortArray.arr[i];
		curr = i;
	    }
	}
	if (min != sortArray.arr[j]) {
		sortArray.arr[curr] = sortArray.arr[j];
		sortArray.arr[j] = min;
	}
    }
}

void SelectionSort::printArray(){
        // prints out the integers in sorted order
    for (int i = 0; i<sortArray.length; i++) {
	std::cout << sortArray.arr[i] << std::endl;
    }
}



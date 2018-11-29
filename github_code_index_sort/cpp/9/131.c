//
//  SelectionSort.cpp
//  Sorts integers using the SelectionSort algorithm


#include "SelectionSort.h"

using namespace std;

SelectionSort::SelectionSort(){ // constructor
        sortArray.length = 0;
        sortArray.arr = NULL;
}

SelectionSort::~SelectionSort(){ //destructor
	delete []sortArray.arr;
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
	if (sortArray.length == 0 || sortArray.length == 1){
		return;
	}
	int tempy = 0;

	for (int i = 0; i < sortArray.length; i++){
		//makes the smallest number place the last unsorted array index.
		int smallestnum = i;
		//finds the ACTUAL smallest unsorted number:
		for (int j = i; j < sortArray.length; j++){
			if (sortArray.arr[j] <= sortArray.arr[smallestnum]){
				smallestnum = j;
			}
		}
		//puts the smallest number in the last unsorted array index.
		tempy = sortArray.arr[i];
		sortArray.arr[i] = sortArray.arr[smallestnum];
		sortArray.arr[smallestnum] = tempy;
	}
	//repeats until the entire array is sorted. 
}

void SelectionSort::printArray(){
        // prints out the integers in sorted order
	for (int i = 0; i < sortArray.length; i++){
		cout << sortArray.arr[i] <<endl;
	}
}



// Written by Grant Pemberton 11/7/2014
//  SelectionSort.cpp
//  Sorts integers using the SelectionSort algorithm


#include "SelectionSort.h"

using namespace std;

SelectionSort::SelectionSort(){ // constructor
        sortArray.length = 0;
        sortArray.arr = NULL;
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

	int minIndex;
	//keeps track of the index of the minimum valued element
	for (int i = 0; i < sortArray.length; i++){
		minIndex = i;//loop through the sortArray
		for (int j = i+1; j < sortArray.length; j++){
		//begin search at the index 1 after i
			if (sortArray.arr[j] < sortArray.arr[minIndex]){
			//if there is a smaller value after index i
				minIndex = j;
				//j is the index that has the smallest value
			}
		}
		if (minIndex != i){//swap step
			
			swap(i, minIndex);
			//in place swap
		}
	}
}

void SelectionSort::printArray(){
        // prints out the integers in sorted order
	
	for (int i = 0; i < sortArray.length; i++){
		cout << sortArray.arr[i] << endl;
	}
}

void SelectionSort::swap(int index1, int index2){
	//swap helper function
	
	int temp = sortArray.arr[index1];
	//use of temp preserves the information in index1
	
	
	//swap the two values
	sortArray.arr[index1] = sortArray.arr[index2];
	sortArray.arr[index2] = temp;
}




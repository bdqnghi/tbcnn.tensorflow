




#include "SelectionSort.h"

using namespace std;

SelectionSort::SelectionSort(){ 
        sortArray.length = 0;
        sortArray.arr = NULL;
}

SelectionSort::~SelectionSort() {
    delete [] sortArray.arr;

}


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
    
    int min = sortArray.arr[0];
    int curr = 0;

    
    
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
        
    for (int i = 0; i<sortArray.length; i++) {
	std::cout << sortArray.arr[i] << std::endl;
    }
}



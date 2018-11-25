




#include "SelectionSort.h"

using namespace std;

SelectionSort::SelectionSort(){ 
        sortArray.length = 0;
        sortArray.arr = NULL;
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


	int minIndex;
	
	for (int i = 0; i < sortArray.length; i++){
		minIndex = i;
		for (int j = i+1; j < sortArray.length; j++){
		
			if (sortArray.arr[j] < sortArray.arr[minIndex]){
			
				minIndex = j;
				
			}
		}
		if (minIndex != i){
			
			swap(i, minIndex);
			
		}
	}
}

void SelectionSort::printArray(){
        
	
	for (int i = 0; i < sortArray.length; i++){
		cout << sortArray.arr[i] << endl;
	}
}

void SelectionSort::swap(int index1, int index2){
	
	
	int temp = sortArray.arr[index1];
	
	
	
	
	sortArray.arr[index1] = sortArray.arr[index2];
	sortArray.arr[index2] = temp;
}




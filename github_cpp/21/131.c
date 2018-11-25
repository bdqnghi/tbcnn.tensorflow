




#include "SelectionSort.h"

using namespace std;

SelectionSort::SelectionSort(){ 
        sortArray.length = 0;
        sortArray.arr = NULL;
}

SelectionSort::~SelectionSort(){ 
	delete []sortArray.arr;
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
        
	if (sortArray.length == 0 || sortArray.length == 1){
		return;
	}
	int tempy = 0;

	for (int i = 0; i < sortArray.length; i++){
		
		int smallestnum = i;
		
		for (int j = i; j < sortArray.length; j++){
			if (sortArray.arr[j] <= sortArray.arr[smallestnum]){
				smallestnum = j;
			}
		}
		
		tempy = sortArray.arr[i];
		sortArray.arr[i] = sortArray.arr[smallestnum];
		sortArray.arr[smallestnum] = tempy;
	}
	
}

void SelectionSort::printArray(){
        
	for (int i = 0; i < sortArray.length; i++){
		cout << sortArray.arr[i] <<endl;
	}
}



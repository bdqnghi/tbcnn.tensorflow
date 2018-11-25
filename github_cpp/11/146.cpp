




#include "heapsort.h"


void heapsort(int * array, int arraySize){
	clock_t begin, end;				
	begin = clock();
	heapsortMain(array, arraySize);
	end = clock();
	std::cout << "\t" << diffClocks(end, begin);
}


void bubbleDown(int * array, int arraySize, int moveThis){
	
	int child = (moveThis * 2) + 1;
	int tempMove = array[moveThis];			
	
	while (child < arraySize){
		
		if((child + 1 < arraySize) && (array[child+1] > array[child])){
			child++;
		}
		
		if(tempMove < array[child]){
			
			array[moveThis] = array[child];
			array[child] = tempMove;
		}

		
		moveThis = child;
		child = (moveThis * 2) +1;
	}
}


void heapsortMain(int * array, int arraySize){
	
	for(int i = (arraySize-1)/2; i >= 0; i--){
		bubbleDown(array, arraySize, i);
	}

	int tempMove = -1;				
	
	for(int i = arraySize - 1; i > 0; i--){
		tempMove = array[0];
		
		array[0] = array[i];
		array[i] = tempMove;
		bubbleDown(array, i , 0);
	}
	
}
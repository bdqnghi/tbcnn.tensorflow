//Aurhtor: Ross Bearden
//Project: Lab Sorting
//File: heapsort.cpp
//Purpose: Supplies the function body for heapsort

#include "heapsort.h"

//This function starts a clock then calls the heap sort function
void heapsort(int * array, int arraySize){
	clock_t begin, end;				//clock variables that will be used to determine the sorting time
	begin = clock();
	heapsortMain(array, arraySize);
	end = clock();
	std::cout << "\t" << diffClocks(end, begin);
}

//This is the implementation of the bubble down method used in the heapsort function
void bubbleDown(int * array, int arraySize, int moveThis){
	//Gets the left child of moveThis in the array
	int child = (moveThis * 2) + 1;
	int tempMove = array[moveThis];			//Holds the value in the array currently being moved
	//As long as moveThis has a child this loop will continue
	while (child < arraySize){
		//Determines if the left or right child is greater
		if((child + 1 < arraySize) && (array[child+1] > array[child])){
			child++;
		}
		//Swaps the parent for the child if the child is bigger
		if(tempMove < array[child]){
			//std:: cout << "Swapping " << tempMove << " with " << array[child] << std::endl;
			array[moveThis] = array[child];
			array[child] = tempMove;
		}

		//Update the index being moved and find the new children, if they exist
		moveThis = child;
		child = (moveThis * 2) +1;
	}
}

//This function uses a heap sort methods to sort the array
void heapsortMain(int * array, int arraySize){
	//Heapify 
	for(int i = (arraySize-1)/2; i >= 0; i--){
		bubbleDown(array, arraySize, i);
	}

	int tempMove = -1;				//Used to move array values
	//Loop swaps top element for last element then bubbles down the new top element
	for(int i = arraySize - 1; i > 0; i--){
		tempMove = array[0];
		//std:: cout << "Moving " << tempMove << " to the sorted portion" << std::endl; 
		array[0] = array[i];
		array[i] = tempMove;
		bubbleDown(array, i , 0);
	}
	/*for( int i = 0; i < arraySize; i++){
		std::cout << array[i] << std::endl;
	}*/
}
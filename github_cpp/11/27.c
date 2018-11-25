

#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <cmath>
#include "Profiler_linux.h"

using namespace std;

Profiler profiler("HeapSorting");


void print(int arr[], int size){
	for (int i = 0; i < size; i++){
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}




int getParent(int node){
	return (floor((node - 1) / 2));
}


int getLeftChild(int node){
	return (2 * node + 1);
}


int getRightChild(int node){
	return (2 * node + 2);
}




void siftUp(int arr[], int start, int end, int *a, int *c){
	int child  = end;
	int parent;

	while (child > start){
		parent = getParent(child);
		(*c)++;
		if (arr[parent] < arr[child]){
			(*a)++;
			swap(arr[parent], arr[child]);
			child = parent;
		}
		else{
			return;
		}
	}
}


void heapifyUp(int arr[], int size, int *a, int *c){
	int end = 1;

	while (end < size){
		siftUp(arr, 0, end, a, c);
		end++;
	}
}


void heapSortUp(int arr[], int size, string caseScenario){
	int a = 0;
	int c = 0;

	
	heapifyUp(arr, size, &a, &c);				

	int end = size - 1;
	while (end > 0){
		a += 3;
		swap(arr[end], arr[0]);						
		heapifyUp(arr, end, &a, &c);			
		
		end--;
	}

	
	profiler.countOperation((caseScenario + "A").c_str(), size, a);
	profiler.countOperation((caseScenario + "C").c_str(), size, c);
	profiler.addSeries((caseScenario + "AC").c_str(), (caseScenario + "A").c_str(), (caseScenario + "C").c_str());
}




void siftDown(int arr[], int start, int end, int *a, int *c){
	int aux;														
	int child;
	int root = start;										

	while(getLeftChild(root) <= end){		
		child = getLeftChild(root);
		aux   = root;
		(*c)++;
		if (arr[aux] < arr[child]){				
			aux = child;
		}																	
		(*c)++;
		if (((child + 1) <= end) && (arr[aux] < arr[child + 1])){
			aux = child + 1;
		}
		if (aux == root){									
			return;													
		}
		else{
			(*a) += 3;
			swap(arr[root], arr[aux]);			
			root = aux;
		}
	}
}


void heapifyDown(int arr[], int size, int *a, int *c){
	int start = getParent(size - 1);

	while (start >= 0){
		siftDown(arr, start, size - 1, a, c);
		start--;
	}
}


void heapSortDown(int arr[], int size, string caseScenario){
	int a = 0;													
	int c = 0;													

	
	heapifyDown(arr, size, &a, &c);			

	int end = size - 1;
	while (end > 0){
		a += 3;
		swap(arr[end], arr[0]);						
		end--;														
		siftDown(arr, 0, end, &a, &c);		
	}
	
	profiler.countOperation((caseScenario + "A").c_str(), size, a);
	profiler.countOperation((caseScenario + "C").c_str(), size, c);
	profiler.addSeries((caseScenario + "AC").c_str(), (caseScenario + "A").c_str(), (caseScenario + "C").c_str());
}


void Test(char *AlgorithmName){
	int arr[100000];

	if (!strcmp("heapSortUp", AlgorithmName)){					
		printf(" ...testing HeapSort Top-Down... \n");
		FillRandomArray(arr, 100, 10, 50000, false, 0);
		heapSortUp(arr, 100, "test");
		if (IsSorted(arr, 100)){
			printf("HeapSort Top-Down works just fine!\n\n");
		}
		else{
			printf("HeapSort Top-Down does not work!\n\n");
		}
	}

	else if (!strcmp("heapSortDown", AlgorithmName)){ 
		printf(" ...testing HeapSort Bottom-Up... \n");
		FillRandomArray(arr, 100, 10, 50000, false, 0);
		heapSortDown(arr, 100, "test");
		if (IsSorted(arr, 100)){
			printf("HeapSort Bottom-up works just fine!\n\n");
		}
		else{
			printf("HeapSort Bottom-up does not work!\n\n");
		}
	}

	else{
		printf("Not an algorithm name!\n\n");
	}
}


void copyArray(int size, int arr1[], int arr2[]){
	for (int i = 0; i < size; i++){
		arr2[i] = arr1[i];
	}
}



int main(){
	int arr[100000];
	int arrCopy[100000];

	
	
	Test("heapSortUp");
	Test("heapSortDown");


	
	profiler.showReport();
	return (0);
}

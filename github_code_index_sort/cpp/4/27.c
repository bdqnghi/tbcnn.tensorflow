/**
 * @author Șinca Mădălina Ștefania
 * @group 30423
 *
 * Compare the following sorting methods: HeapSort (botoom-up and top down approaches)
 *
 * for heapSortDown (bottom-up approach)
 *
 * for both methods, the complexity should be (in both best and worst cases) O(nlogn)
 * since the implementation needs O(n) time to compute the maxHeap / heapify the array
 * and it takes Sum[ O(logi)], i->n, to sort it; O(n) + Sum = O(nlogn);
 *
 * nevertheless, the implementation I chose might be faulty, since I decided I can not
 * use siftUp as a means of fixing the heap during the sort (I am using heapify at each step
 * for reconstruction), thus resulting in much more complexity than needed in top-down approach,
 * and that is why the graphs look much more different than they should, I suppose.
 */

#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <cmath>
#include "Profiler_linux.h"

using namespace std;

Profiler profiler("HeapSorting");

// prints array, useful in debugging
void print(int arr[], int size){
	for (int i = 0; i < size; i++){
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}

// Heap maps

// returns the parent of the node
int getParent(int node){
	return (floor((node - 1) / 2));
}

// returns the left child of node
int getLeftChild(int node){
	return (2 * node + 1);
}

// returns the right child of node
int getRightChild(int node){
	return (2 * node + 2);
}

// top-down approach

// bubbles up any children nodes that have a bigger value than their parent nodes
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

// creates the heap structure inside the array using the top-down approach
void heapifyUp(int arr[], int size, int *a, int *c){
	int end = 1;

	while (end < size){
		siftUp(arr, 0, end, a, c);
		end++;
	}
}

// main algorithm
void heapSortUp(int arr[], int size, string caseScenario){
	int a = 0;
	int c = 0;

	// sorting
	heapifyUp(arr, size, &a, &c);				// create heap structure in array

	int end = size - 1;
	while (end > 0){
		a += 3;
		swap(arr[end], arr[0]);						// place the max element on the last index
		heapifyUp(arr, end, &a, &c);			// recreate heap structure
		//siftDown(arr, 0, end, &a, &c);
		end--;
	}

	// profiler usage
	profiler.countOperation((caseScenario + "A").c_str(), size, a);
	profiler.countOperation((caseScenario + "C").c_str(), size, c);
	profiler.addSeries((caseScenario + "AC").c_str(), (caseScenario + "A").c_str(), (caseScenario + "C").c_str());
}

// bottom-up approach

//
void siftDown(int arr[], int start, int end, int *a, int *c){
	int aux;														// aux will always store the node which must be swapped with the root
	int child;
	int root = start;										// starting from the root / max element

	while(getLeftChild(root) <= end){		// while not at the end of heap
		child = getLeftChild(root);
		aux   = root;
		(*c)++;
		if (arr[aux] < arr[child]){				// checks left child
			aux = child;
		}																	// checks right child
		(*c)++;
		if (((child + 1) <= end) && (arr[aux] < arr[child + 1])){
			aux = child + 1;
		}
		if (aux == root){									// left and right children are smaller than root
			return;													// exit procedure
		}
		else{
			(*a) += 3;
			swap(arr[root], arr[aux]);			// put bigger child on first position
			root = aux;
		}
	}
}

// creates the heap structure inside the array using the bottom-up approach
void heapifyDown(int arr[], int size, int *a, int *c){
	int start = getParent(size - 1);

	while (start >= 0){
		siftDown(arr, start, size - 1, a, c);
		start--;
	}
}

// main algorithm
void heapSortDown(int arr[], int size, string caseScenario){
	int a = 0;													// number of assignments
	int c = 0;													// number of comparisons

	// sorting
	heapifyDown(arr, size, &a, &c);			// heap structure is created

	int end = size - 1;
	while (end > 0){
		a += 3;
		swap(arr[end], arr[0]);						// place the max element on the last index
		end--;														// decrease the size of unordered array / heap
		siftDown(arr, 0, end, &a, &c);		// recreate heap structure
	}
	// profiler usage
	profiler.countOperation((caseScenario + "A").c_str(), size, a);
	profiler.countOperation((caseScenario + "C").c_str(), size, c);
	profiler.addSeries((caseScenario + "AC").c_str(), (caseScenario + "A").c_str(), (caseScenario + "C").c_str());
}

// tests the algorithm's correctnesss
void Test(char *AlgorithmName){
	int arr[100000];

	if (!strcmp("heapSortUp", AlgorithmName)){					// tests Bubble Sort
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

	else if (!strcmp("heapSortDown", AlgorithmName)){ // tests Insertion Sort
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

// copies arr1 of size in arr2
void copyArray(int size, int arr1[], int arr2[]){
	for (int i = 0; i < size; i++){
		arr2[i] = arr1[i];
	}
}

// main function

int main(){
	int arr[100000];
	int arrCopy[100000];

	// testing algorithm correctness
	// tests should be run separately in regards to the profiler
	Test("heapSortUp");
	Test("heapSortDown");
/*
for(int nbOfElements = 100; nbOfElements <= 10000; nbOfElements += 100){
	// best case
	FillRandomArray(arr, nbOfElements, 1, 50000, true, 2);
	heapSortUp(arr, nbOfElements, "BestUp");
	FillRandomArray(arr, nbOfElements, 1, 50000, true, 2);
	heapSortDown(arr, nbOfElements, "BestDown");

	// average case
	for(int i = 0; i < 5; i++){
		FillRandomArray(arr, nbOfElements, 1, 50000, false, 0);
		copyArray(nbOfElements, arr, arrCopy);
		heapSortUp(arr, nbOfElements, "AverageUp");
		heapSortDown(arrCopy, nbOfElements, "AverageDown");
	}

	// worst case
	FillRandomArray(arr, nbOfElements, 1, 50000, false, 1);
	heapSortUp(arr, nbOfElements, "WorstUp");
	FillRandomArray(arr, nbOfElements, 1, 50000, false, 1);
	heapSortDown(arr, nbOfElements, "WorstDown");
}

//generate profiler groups
profiler.createGroup("1_BestCaseAssignments", 		"BestUpA", 		"BestDownA");
profiler.createGroup("2_BestCaseComparisons", 		"BestUpC", 		"BestDownC");
profiler.createGroup("3_BestCaseSum", 						"BestUpAC",		"BestDownAC");

profiler.createGroup("4_AverageCaseAssignments",  "AverageUpA", "AverageDownA");
profiler.createGroup("5_AverageCaseComparisons",  "AverageUpC", "AverageDownC");
profiler.createGroup("6_AverageCaseSum",				  "AverageUpAC","AverageDownAC");

profiler.createGroup("7_WorstCaseAssignments",    "WorstUpA", 	"WorstDownA");
profiler.createGroup("8_WorstCaseComparisons",    "WorstUpC", 	"WorstDownC");
profiler.createGroup("9_WorstCaseSum", 				    "WorstUpAC",	"WorstDownAC");
*/

	// generate the reports
	profiler.showReport();
	return (0);
}

// Written by Grant Pemberton 11/7/2014
//  ShellSort.cpp
//  Sorts integers using the ShellSort algorithm

#include <cmath>
#include "sort3.h"

using namespace std;

ShellSort::ShellSort(){ // constructor
        sortArray.length = 0;
        sortArray.arr = NULL;
}

// reads in a list of integers from stdin and returns an arrayWithLength
void ShellSort::readList(){
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

void ShellSort::sort(){
// Shell sort on sortArray, takes into account what gap size algorithm 
// should be used
// Note: this shell sort uses a hybrid gapsize, so it's asymptotic complexity
//	 is going to be strange

	//Ciura Gap Array(CGA) was found experimentally in 2001
	//Hibbard Gap Array(HGA) can be infinite (accomodate very large arrays)
	if (sortArray.length <= 50000){
		CiuraShellSort();
		//For less than 50000 elements, the CGA beats HGS
	}else{
		HibbardShellSort();
	}
}

void ShellSort::CiuraShellSort(){

	int gaps [8] = { 701, 301, 132, 57, 23, 10, 4, 1};//Ciura's gap array
	
	for (int g = 0; g < 8; g++){
		for (int i = 1; i < sortArray.length; i++){//loop through array
			//NOTE: zeroeth element is checked below
			int j = i;
			while((j>0&&j-gaps[g]>=0)&&
				((sortArray.arr[j-gaps[g]]>sortArray.arr[j]))){

				//if element is greater than its next element
				//then swap them
				swap(j, (j-gaps[g]));
				//j-1 is the new index in question
				j -= gaps[g];
			}
		}
	}
}

void ShellSort::HibbardShellSort(){

	int gapSize [30];//this array size should cover up to 2^30 inputs
	int gapLimit = 30;
	//gapLimit is the index of which gap should be used to start the 
	//shell sort because one would not want to start with a gap that
	//is much larger than the actual amount of data
	for (int i = 0; i < 30; i++){
		gapSize[i] = HibbardGapSize(i+1);
		//use i+1 for HGS b/c i=0 produces a gapsize of 0
		if (sortArray.length > gapSize[i]){
			gapLimit = i;
		}
	}
	for (int g = gapLimit; g >=0; g--){//traverse gap array backwards
		for (int i = 1; i < sortArray.length; i++){//loop through array
			//NOTE: zeroeth element is checked below
			int j = i;
			while ((j > 0 && j-gapSize[g] >= 0) && 
				((sortArray.arr[j-gapSize[g]] > 
				sortArray.arr[j]))){
				
				//checks in bounds of array (because we check (j-1))
				//if an element is greater than its next element
				//then swap them
				swap(j, (j-gapSize[g]));
				//j-1 is the new index in question
				j -= gapSize[g];
			}
		}
	}
}

void ShellSort::printArray(){
        // prints out the integers in sorted order
	
	for (int i = 0; i < sortArray.length; i++){
		cout << sortArray.arr[i] << endl;
	}
}


void ShellSort::swap(int index1, int index2){
	//swap helper function
	
	int temp = sortArray.arr[index1];
	//use of temp preserves the information in index1
	
	
	//swap the two values
	sortArray.arr[index1] = sortArray.arr[index2];
	sortArray.arr[index2] = temp;
}

int ShellSort::HibbardGapSize(int k){
	//for increasing values of k, this function will give the ordered list,
	//{1, 3, 7, 15, 31, 63, ...}   
	
	if (k>0){
		return (int)(pow(2,k)-1);
		//re-caste output of power() to an int for convenience
	}else{
		return 1;
	}
}
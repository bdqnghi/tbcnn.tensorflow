



#include <cmath>
#include "sort3.h"

using namespace std;

ShellSort::ShellSort(){ 
        sortArray.length = 0;
        sortArray.arr = NULL;
}


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





	
	
	if (sortArray.length <= 50000){
		CiuraShellSort();
		
	}else{
		HibbardShellSort();
	}
}

void ShellSort::CiuraShellSort(){

	int gaps [8] = { 701, 301, 132, 57, 23, 10, 4, 1};
	
	for (int g = 0; g < 8; g++){
		for (int i = 1; i < sortArray.length; i++){
			
			int j = i;
			while((j>0&&j-gaps[g]>=0)&&
				((sortArray.arr[j-gaps[g]]>sortArray.arr[j]))){

				
				
				swap(j, (j-gaps[g]));
				
				j -= gaps[g];
			}
		}
	}
}

void ShellSort::HibbardShellSort(){

	int gapSize [30];
	int gapLimit = 30;
	
	
	
	for (int i = 0; i < 30; i++){
		gapSize[i] = HibbardGapSize(i+1);
		
		if (sortArray.length > gapSize[i]){
			gapLimit = i;
		}
	}
	for (int g = gapLimit; g >=0; g--){
		for (int i = 1; i < sortArray.length; i++){
			
			int j = i;
			while ((j > 0 && j-gapSize[g] >= 0) && 
				((sortArray.arr[j-gapSize[g]] > 
				sortArray.arr[j]))){
				
				
				
				
				swap(j, (j-gapSize[g]));
				
				j -= gapSize[g];
			}
		}
	}
}

void ShellSort::printArray(){
        
	
	for (int i = 0; i < sortArray.length; i++){
		cout << sortArray.arr[i] << endl;
	}
}


void ShellSort::swap(int index1, int index2){
	
	
	int temp = sortArray.arr[index1];
	
	
	
	
	sortArray.arr[index1] = sortArray.arr[index2];
	sortArray.arr[index2] = temp;
}

int ShellSort::HibbardGapSize(int k){
	
	
	
	if (k>0){
		return (int)(pow(2,k)-1);
		
	}else{
		return 1;
	}
}
#include<cstdio>
#include<iostream>

using namespace std;

void selectionSort(int arr[], int size){
	//Algorithm : selective
	//Time : O(n^2)
	//Space : O(1)
	int minIdx;
	for(int i=0; i<(size-1); ++i){
		minIdx = i;
		for(int j=i+1; j < size; j++){
			if(arr[j] < arr[minIdx]){
				minIdx = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[minIdx];
		arr[minIdx] = temp;
	}
}

int main(){
	int a[] = {2,5,1,0,7,8,10,9};
	
	int size = sizeof(a)/sizeof(int);
	printf("Before Sorting...\n");
	for(int i=0; i<size; ++i){
		printf("%d ",a[i]);
	}
	printf("\n");
	
	selectionSort(a,size);
	
	printf("After Sorting...\n");
	for(int i=0; i<size; ++i){
		printf("%d ",a[i]);
	}
	printf("\n");
	return 0;
}

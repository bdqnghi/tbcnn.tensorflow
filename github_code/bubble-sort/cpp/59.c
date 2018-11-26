#include<cstdio>
#include<iostream>

using namespace std;

void bubbleSort(int arr[],int size){
	//Algorithm : Iterative
	//Time : O(n^2)
	//Space : O(1)
	for(int i=0; i<size; ++i){
		for(int j=0; j<(size-1-i); ++j){
			if(arr[j] > arr[j+1]){
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
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
	
	bubbleSort(a,size);
	
	printf("After Sorting...\n");
	for(int i=0; i<size; ++i){
		printf("%d ",a[i]);
	}
	printf("\n");
	
	
	return 0;
}

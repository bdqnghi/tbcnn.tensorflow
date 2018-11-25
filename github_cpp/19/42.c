



















#include <stdio.h>

int Quicksort(int arr[], int left, int right){
	int pivot = arr[left]; 
	int low = left+1; 
	int high = right; 
	int _sav; 
	
	while(low<=high){
		while(arr[low]>=pivot && low<=right){ 
			low++;
		}
		
		while(arr[high]<=pivot && high>=left+1){ 
			high--;
		}
		
		if(low<=high){_sav=arr[low]; arr[low]=arr[high]; arr[high]=_sav;} 
	}
	
	_sav=arr[high]; arr[high]=pivot; arr[left]=_sav;
	return high; 
}

void QuickNsort(int arr[], int left, int right){
	if(left<=right){
		int pivot = Quicksort(arr, left, right);
		QuickNsort(arr, left, pivot-1); 
		QuickNsort(arr, pivot+1, right); 
	}
}
	

int main(){
    int test[10] = {2,1,6,87,47,3,78,43,0,46};
    
    QuickNsort(test, 0, 9);
    
    for(int i=0; i<10; i++)printf("%d ",test[i]);
} 

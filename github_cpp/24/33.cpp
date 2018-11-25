#include<cstdio>
#include<iostream>

using namespace std;

int binarySearch(int arr[],int l,int r,int x){
	
	
	
	while(l <= r){
		int mid = l+(r-1)/2;
		if(arr[mid] == x ){
			return mid;
		}
		if(arr[mid] < x){
			l = mid+1;	
		}else{
			r = mid-1;  
		}		
	}
	return -1;
}
int main(){
	int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr)/ sizeof(arr[0]);
    int x = 10;
    int idx = binarySearch(arr, 0, n-1, 10);
    printf("The element %d found at index %d\n",x,idx);
	return 0;
}

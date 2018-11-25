#include<iostream>
using namespace std;

int binary_search_cpp(int arr[], int low, int high, int target){
    
    int mid = (low+high)/2;
    
    if(arr[mid] == target) return mid;
    
    if(arr[mid] > target) return binary_search_cpp(arr, low, mid, target);
    if(arr[mid] < target) return binary_search_cpp(arr, mid+1, high, target);
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr)/sizeof(arr[0]);
    int target = 7;

	cout<< target << " is at index " << binary_search_cpp(arr, 0, n, target) <<endl;

	return 0;
}


#include <bits/stdc++.h>
using namespace std;
void quicksort(int arr[], int low, int high) {
	if(low >= high) return;
	
	int walltill = low - 1, pivot = arr[high];
	for(int i = low; i <= high - 1; i++) {
		
		if(arr[i] <= pivot) {
			swap(arr[walltill + 1], arr[i]);
			walltill++;
		}
	}
	
	swap(arr[high], arr[walltill + 1]);
	
	quicksort(arr, low, walltill);
	quicksort(arr, walltill + 2, high);
}

int main () {
	int n; cin>>n;
	int arr[n];
	for(int i = 0; i < n; i++) cin>>arr[i];
	quicksort(arr, 0, n-1);
	for(int i = 0; i < n; i++) cout<<arr[i]<<" ";
	return 0;
}

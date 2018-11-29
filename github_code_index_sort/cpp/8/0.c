#include <bits/stdc++.h>
using namespace std;

int partition(int *arr,int p ,int r){
	int pivot = arr[r];
	int i = p-1;
	for(int j = p; j<=r-1;j++){
		if(arr[j] <= pivot){
			i++;
			swap(arr[j],arr[i]);
		}
	}
	swap(arr[i+1],arr[r]);
	return i+1;
}

/*void quicksort(int *arr,int p ,int r ){
  if(p < r){
 	int q = partition(arr,p,r);
 	quicksort(arr,p,q-1);
 	quicksort(arr,q+1,r);
  }
}

*/

int main(){
  int arr[5] = { 1,1,1,1,0 };
  partition(arr,0,4);
  for(int i = 0; i< 5;i++) cout << arr[i] << " ";
  cout << endl;
 return 0;
}

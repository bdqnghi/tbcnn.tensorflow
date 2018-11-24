#include<iostream>
using namespace std;
/* 大根堆的调整，时间复杂度为O(logn)  */
void Max_Heapify(int a[], int k, int size){
	int l = (k+1) * 2 -1;
	int r = (k+1) * 2;
	int large = k;
	if(l<size&&a[l]>a[k]){
		large = l;
	}
	if(r<size&&a[r]>a[large]){
		large = r;
	}
	if(large!=k){
		int temp = a[k];
		a[k] = a[large];
		a[large] = temp;
		Max_Heapify(a, large, size);
	}
}
/* 大根堆建立，时间复杂度O(nlogn)  */
void Build_Max_Heap(int a[], int size){
	for(int i=size/2;i>=0;i--){
		Max_Heapify(a, i, size);
	}
}
/* 堆排序算法，不稳定的内排序，时间复杂度为O(nlogn) */
void Heap_sort(int a[], int n){
	Build_Max_Heap(a, n);
	int key = n-1;
	int size = n;
	while(key>0){
		int temp = a[0];
		a[0] = a[key];
		a[key] = temp;
		size--;
		Max_Heapify(a, 0, size);
		key--;
		//Max_Heapify(a, 0, size);
	}
}
int main(){
	int a[7] = {8, 2, 5, 4, 6, 9, 7};
	Heap_sort(a, 7);
	for(int i=0;i<7;i++)
		cout<<a[i]<<",";
	cout<<endl;
	int  b[11] = {1, 5, 8, 5, 0, 6, 7, 6, 5, 8, 3};
	Heap_sort(b, 11);
	for(int i=0;i<11;i++)
		cout<<b[i]<<",";
	cout<<endl;
	return 0;
}

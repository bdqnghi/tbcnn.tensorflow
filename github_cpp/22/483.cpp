#include "stdio.h"

void swap(int &a,int &b){                  //swap a and b
	a=a+b;
	b=a-b;
	a=a-b;
}

void maxHeap(int *a,int n,int i){         //adjust heap
	int left,right,largest;
	left=largest=2*i;

	if(left>n)
		return;

	right=2*i+1;

	if(right<=n && a[left]<a[right]){
		largest=right;
	}
	
	if(a[i]<a[largest]){
		swap(a[i],a[largest]);
		maxHeap(a,n,largest);
	}
}

void creatHeap(int *a,int n){
	int i;
	for(i=n/2;i>=1;i--){
		maxHeap(a,n,i);
	}
}

void HeapSort(int *a,int n){
	creatHeap(a,n);
	for(int i=1;i<n;i++){
		swap(a[1],a[n-i+1]);
		maxHeap(a,n-i,1);
	}
}

				

int main(){
	int a[]={0,3,5,8,9,1,2};
	HeapSort(a,6);
	for(int i=0;i<6;i++){
		printf("%d ",a[i+1]);
	}
	printf("\n");
	int m=1;
	int n=100;
	printf("%d %d\n",m,n);
	swap (m,n);
	printf("%d %d\n",m,n);
}



	
	
	

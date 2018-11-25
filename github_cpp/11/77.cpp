#include<iostream>

using namespace std;


int left(int n){
	return 2*n;
}

int right(int n){
	return (2*n+1);
}

void minheapify(int a[],int n,int heapsize){
	int l = left(n);
	int r = right(n);
	int small = n;
	if(a[small]>a[l] && l < heapsize){
		small = l;
	}
	if(a[small]>a[r] && r < heapsize){
		small = r;
	}
	if(small != n){
		int temp = a[n];
		a[n] = a[small];
		a[small] = temp;
		minheapify(a,small,heapsize);
	}
}

void heapsort(int a[],int heapsize){
	for(int i = heapsize/2; i >= 0;i--){
		minheapify(a,i,heapsize);
	}
	int t = heapsize;
	for(int i = 0; i < t;i++){
		int temp = a[0];
		a[0] = a[heapsize-1];
		a[heapsize-1] = temp;
		heapsize--;		
		minheapify(a,0,heapsize);
	}
}

int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n];
		for(int i = 0; i < n;i++){
			cin>>a[i];
		}
		heapsort(a,n);
		for(int i = n-1; i >= 0;i--){
			cout<<a[i]<<" ";
		}
		cout<<endl;
	}
}
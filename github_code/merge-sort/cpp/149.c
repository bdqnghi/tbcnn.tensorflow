#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define loop(i,N) for(int i=0;i<N;i++)
#define loop_(i,N) for(int i=1;i<=N;i++)

vector <int> ar;

void merge(int low,int mid,int high){
	int l1=mid-low+1;
	int l2=high-mid;
	int aux1[l1],aux2[l2]; // two auxillary arrays that would contain the two sorted lists
	loop(i,l1)
		aux1[i]=ar[low+i];
	loop(i,l2)
		aux2[i]=ar[mid+1+i];
	int i=0,j=0;
	while(i<l1 and j<l2){
		if(aux1[i]<aux2[j])
			ar[low++]=aux1[i++];
		else
			ar[low++]=aux2[j++];
	}
	while(i<l1){	// simply merge the remaining , if any
		ar[low++]=aux1[i++];
	}
	while(j<l2){	// simply merge the remaining, if any
		ar[low++]=aux2[j++];
	}
}

void mergeSort(int low,int high){
	if(low<high){
		int mid=(low+high)/2;	// or a fancy way to avoid integer overflow for large array sizes
		mergeSort(low,mid);
		mergeSort(mid+1,high);
		merge(low,mid,high);
	}
}

int main(){
	int n,num;
	cin>>n;
	loop(i,n)	cin>>num, ar.push_back(num);
	mergeSort(0,n-1);
	loop(i,n)	cout<<ar[i]<<" ";
	cout<<endl;
	return 0;
}

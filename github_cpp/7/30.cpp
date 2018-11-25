 
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#define random(x) (rand()%x)
#define  Iter	vector<int>::iterator
#define  INF	0x7fffffff
using namespace std;
vector<int> array;
int arrLen = 20;

void initData(vector<int>& array){
	for(int i=0;i<arrLen;++i)
		array.push_back(random(100));
}


void merge(Iter begin, Iter mid, Iter end){
	vector<int> arr1(begin,mid+1);
	vector<int> arr2(mid+1,end+1);
	
	arr1.insert(arr1.end(), INF);
	arr2.insert(arr2.end(), INF);
	
	
	Iter pt1 = arr1.begin();
	Iter pt2 = arr2.begin();
	for(Iter it = begin;it<=end;++it){
		if(*pt1<=*pt2){
			*it = *pt1;
			pt1++;
		}
		else{
			*it = *pt2;
			pt2++;
		}
	}
	
}


void MergeSort(Iter begin,Iter end){
	if(begin<end){
		Iter mid = begin + (end - begin)/2;
		MergeSort(begin, mid);
		MergeSort(mid+1,end);
		
		
		merge(begin,mid,end);
	}
}

void print(vector<int>& array){
	for(int i=0;i<array.size();++i)
		cout<<array[i]<<" ";
	cout<<endl;
}
int main(){
	initData(array);
	cout<<"before sort:"<<endl;
	print(array);
	MergeSort(array.begin(),array.end()-1);
	cout<<"after sort:"<<endl;
	print(array);
}

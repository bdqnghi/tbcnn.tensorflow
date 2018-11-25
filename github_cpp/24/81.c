



#include "stdafx.h"
#include<iostream>
#include<conio.h>

using namespace std;

void sort(int array1[],int arraysize);
int binarysearch(int array1[],int key,int low,int high,int arraysize);


int _tmain(int argc, _TCHAR* argv[])
{
	int arraysize;
	cout<<"input arraysize:";
	cin>>arraysize;
	int *array1=new int[arraysize];
	for(int i=0;i<arraysize;i++){
		cout<<"\ninput array[ "<<i+1<<" ]= ";
		cin>>array1[i];
	}
	for(int i=0;i<arraysize;i++)
		cout<<array1[i]<<" ";
	sort(array1,arraysize);
	int key;
	cout<<"\ninput your key:";
	cin>>key;
	int low=0,high=arraysize-1;
	int h=binarysearch(array1,key,low,high,arraysize);
	cout<<endl;
	for(int i=0;i<arraysize;i++)
		cout<<array1[i]<<" ";
	cout<<endl<<h;
	getch();
	return 0;
}

void sort(int array1[],int arraysize){
	int hold;
	for(int i=0;i<arraysize;i++){
		for(int j=i+1;j<arraysize;j++){
			if(array1[j]<array1[i]){
				hold=array1[j];
				array1[j]=array1[i];
				array1[i]=hold;
			}
		}
	}
}



int binarysearch(int array1[],int key,int low,int high,int arraysize){
	int middle;
	while(low<=high){
		middle=(low+high)/2;
		if(key==array1[middle])
			return middle;
		else if(key<array1[middle])
			high=middle-1;
		else
			low=middle+1;
	}
	return -1;
}




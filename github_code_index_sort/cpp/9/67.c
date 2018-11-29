//////////////////////////////////////////////////////////////////////////
// FileName:    SelectionSort.cpp
// Description: Contains the implementation file for the Class SelectionSort. This class will sort the given
//				array and vector (small and large) through two algorithm techniques, Iteration & Recursion. 
// Author:      Bharath Darapu
// Project:     HomeWork4 
//////////////////////////////////////////////////////////////////////////


#include<iostream>
#include<conio.h>
#include "SelectionSort.h"

using namespace std;


//Selection sort function 
//Iterative selection sort for arrays
void SelectionSort::IterationSort(int arr[],int size,char order)
{
	if(order=='a'||order=='A')
	{
		cout<<"\nSorting Array through Iteration Sort in ascending order";
		IterationSort_asc(arr,size);
		
	}
	else if(order=='d'||order=='D')
	{
		cout<<"\nSorting Array through Iteration Sort in descending order";
		IterationSort_desc(arr,size);
	}
}

//Selection sort function 
//Iterative selection sort for vectors
void SelectionSort::IterationSort(vector<int> &vector_item,int size,char order)
{
	if(order=='a'||order=='A')
	{
		cout<<"\nSorting Vector through Iteration Sort in ascending order";
		IterationSort_asc(vector_item,size);
		
	}
	else if(order=='d'||order=='D')
	{
		cout<<"\nSorting vector through Iteration Sort in descending order";
		IterationSort_desc(vector_item,size);
	}
}

//Selection sort function 
//Iterative selection sort for arrays in ascending order
void SelectionSort:: IterationSort_asc(int arr[] ,int size)
 {
	 
	 
	 int j=0;
	 for(int i=0;i<size;i++)
	 {
	   int temp=arr[i];
		for(int j=i;j<=size-1;j++)
		{
	      if(temp>arr[j])
	      {
		   temp=temp+arr[j];
		   arr[j]=temp-arr[j];
		   temp=temp-arr[j];
	      }
		}
		arr[i]=temp;
	 }
 }

//Selection sort function 
//Iterative selection sort for arrays in descending order
void SelectionSort:: IterationSort_desc(int arr[] ,int size)
 {
	 
	 
	 int j=0;
	 for(int i=0;i<size;i++)
	 {
	   int temp=arr[i];
		for(int j=i;j<=size-1;j++)
		{
	      if(temp<arr[j])
	      {
		   temp=temp+arr[j];
		   arr[j]=temp-arr[j];
		   temp=temp-arr[j];
	      }
	    }
		arr[i]=temp;
	 }
 }

//Selection sort function 
//Iterative selection sort for vectors in ascending order
void SelectionSort::IterationSort_asc(vector<int> &vector_item ,int size)
{
	
	
	int j=0;
	 for(int i=0;i<size;i++)
	 {
		 int temp=vector_item[i];
		for(int j=i;j<=size-1;j++)
		{
	      if(temp>vector_item[j])
	      {
		   temp=temp+vector_item[j];
		   vector_item[j]=temp-vector_item[j];
		   temp=temp-vector_item[j];
	      }
		}
		vector_item[i]=temp;
	 }
}

//Selection sort function 
//Iterative selection sort for vector in descending order
void SelectionSort::IterationSort_desc(vector<int> &vector_item ,int size)
{

	 
	 int j=0;
	 for(int i=0;i<size;i++)
	 {
		 int temp=vector_item[i];
		for(int j=i;j<=size-1;j++)
		{
	      if(temp<vector_item[j])
	      {
		   temp=temp+vector_item[j];
		   vector_item[j]=temp-vector_item[j];
		   temp=temp-vector_item[j];
	      }
		}
		vector_item[i]=temp;
	 }
}


//Selection sort function 
//Recursive selection sort for arrays
void SelectionSort::RecursiveSort(int arr[],int size,char order)
{
	if(order=='a'||order=='A')
	{
		cout<<"\nSorting Array through Recursion Sort in ascending order";
		RecursiveSort_asc(arr,size);
	}
	else if(order=='d'||order=='D')
	{
		cout<<"\nSorting Array through Recursive Sort in descending order";
		RecursiveSort_desc(arr,size);
	}
}



//Selection sort function 
//Recursive selection sort for arrays in ascending order
void SelectionSort::RecursiveSort_asc(int arr[],int size)
  {

	int i,min_index,largest=0,start_index=0;
	min_index=start_index;
	if(size==0)
		return;
	for(i=0;i<size;i++)
	{
		if(arr[i]>largest)
	 {
		largest=arr[i];
		 min_index=i;
	 }
	}
	    
	int temp=arr[size-1];
	arr[min_index]=temp;
	arr[size-1]=largest;

		
			RecursiveSort_asc(arr,--size);
  }


//Selection sort function 
//Recursive selection sort for arrays in descending order
void SelectionSort::RecursiveSort_desc(int arr[],int size)
  {

    
    int i,min_index,start_index=0;
	int largest=arr[start_index];
	min_index=start_index;
	if(size==0)
		return;
	for(i=0;i<size;i++)
	{
	     if(largest>arr[i])
	     {
		   largest=arr[i];
		   min_index=i;
	     }
	   
	}
	    
	int temp=arr[size-1];
	arr[min_index]=temp;
	arr[size-1]=largest;

	RecursiveSort_desc(arr,--size);
  }



//Selection sort function 
//Recursive selection sort for vectors
void SelectionSort::RecursiveSort(vector<int> &vector_item,int size,char order)
{
	if(order=='a'||order=='A')
	{
		cout<<"\nSorting vector through Recursive Sort in ascending order";
		RecursiveSort_asc(vector_item,size);
	}
	else if(order=='d'||order=='D')
	{
		cout<<"\nSorting vector through recursive Sort in descending order";
		RecursiveSort_desc(vector_item,size);
	}
}


//Selection sort function 
//Recursive selection sort for vectors in ascending order
void SelectionSort::RecursiveSort_asc(vector<int> &vector_item,int size)
{

	
	int i,min_index,start_index=0,largest=0;
	min_index=start_index;
	for(i=start_index;i<size;i++)
	{
		if(vector_item[i]>largest)
			{
				largest=vector_item[i];
			    min_index=i;
		}
	}
	    
	int temp=vector_item[size-1];
	vector_item[min_index]=temp;
	vector_item[size-1]=largest;

		if(size>1)
			RecursiveSort_asc(vector_item,--size);
}



//Selection sort function 
//Recursive selection sort for vectors in descending order
void SelectionSort::RecursiveSort_desc(vector<int> &vector_item,int size)
{

	
	int i,min_index,start_index=0,largest=vector_item[start_index];
	min_index=start_index;
	for(i=start_index;i<size;i++)
	{
		if(vector_item[i]<largest)
			{
				largest=vector_item[i];
			    min_index=i;
		    }
	}
	    
	int temp=vector_item[size-1];
	vector_item[min_index]=temp;
	vector_item[size-1]=largest;

		if(size>1)
			RecursiveSort_desc(vector_item,--size);
}
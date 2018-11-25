#include <iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
						 

void PrintArray(int* array, int n);
void QuickSort(int* array, int firstvalue, int endvalue);
int PartitionArray(int* array, int pivot, int firstvalue, int endvalue);
void Swap(int &a, int &b);

int main(void)
{

	

	int array[5];
	cout<<"Enter 5 numbers into the array: " <<endl<<endl;
	
	for(int i = 0; i < 5; i++)				
	{
		 
		 cin>>array[i];
	}
	cout<<endl;
	
	
	clock_t begin=clock();
	
	QuickSort(array,0,4);				
	cout<<endl<<"The sorted array is : "<<endl;
	PrintArray(array, 5);
	
	
			
	clock_t end=clock();
	cout<<"total time is "<<double(end-begin);
	cout<<endl<<endl;
	
	system("PAUSE");
	return 0;
}



void Swap(int &a, int &b)
{
	int hold;
	hold = a;
	a = b;
	b = hold;
}



void PrintArray(int* array, int n)
{
	
	for(int i = 0; i < n; i++) cout<<array[i]<<endl<<endl;
}




void QuickSort(int* array, int firstvalue, int endvalue)
{
	int pivot = array[firstvalue];					
	int splitPoint;
	
	if(endvalue > firstvalue)						
	{
		splitPoint = PartitionArray(array, pivot, firstvalue, endvalue);
													  
		array[splitPoint] = pivot;
		QuickSort(array, firstvalue, splitPoint-1);   
		QuickSort(array, splitPoint+1, endvalue);	 
	}
}



int PartitionArray(int* array, int pivot, int firstvalue, int endvalue)
{
	int leftBoundary = firstvalue;
	int rightBoundary = endvalue;
	
	while(leftBoundary < rightBoundary)			   
	{
		 while( pivot < array[rightBoundary]		  
				&& rightBoundary > leftBoundary)	  
		 {
			  rightBoundary--;						
		 }
		 Swap(array[leftBoundary], array[rightBoundary]);
		 
		 
		 while( pivot >= array[leftBoundary]		  
				&& leftBoundary < rightBoundary)	 
		 {
			  leftBoundary++;						 
		 }
		 Swap(array[rightBoundary], array[leftBoundary]);
		 
	}
	return leftBoundary;							  

}

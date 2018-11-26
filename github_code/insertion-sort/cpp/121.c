/*
Program: Insertion Sort
Author Name:  Sanchit Karve A.K.A 
Usage: insertionsort 
Revision:   V.2010.2.1  
*/

#include <iostream>
using namespace std;
#define ELEMENTS 6

void insertion_sort(int x[],int length)
{
  int key,i;
  for(int j=1;j<length;j++)
  {
     key=x[j];
     i=j-1;
     while(x[i]>key && i>=0)
     {
               x[i+1]=x[i];
         i--;
     }
     x[i+1]=key;
  }
}

int main()
{
  int A[ELEMENTS]={5,2,4,6,1,3};
  int x;

  cout<<"NON SORTED LIST:"<<endl;
  for(x=0;x<ELEMENTS;x++)
  {
       cout<<A[x]<<endl;
  }
  insertion_sort(A,ELEMENTS);
  cout<<endl<<"SORTED LIST"<<endl;
  for(x=0;x<ELEMENTS;x++)
  {
       cout<<A[x]<<endl;
  }
  return 0;
}

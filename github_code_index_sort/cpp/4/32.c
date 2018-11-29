#include<iostream>
using namespace std;
struct htnode
{
    int size;
    int* ar;
};
void swap(int* a, int* b)
 { int t = *a;
  *a = *b; 
   *b = t; 
   }
 
 htnode* createHeap(int *ar, int size)
 {   int i;
    htnode*H = new htnode;
    H->size = size;   
    H->ar = ar;
    for (i = (H->size - 2) / 2; i >= 0; --i)
       // maxfind(H, i);
       return H;
  }
void heapSort(int* ar, int size)
{ 
     htnode* H ;
   H=createHeap(ar, size);
    while (H->size > 1)
    {
        swap(&H->ar[0], &H->ar[H->size - 1]);
        --H->size;  
      //  maxfind(H, 0);
    }
}
void printArray(int* ar, int size)
{
    int i;
    for (i = 0; i < size; ++i)
       cout<< ar[i];
}
int main()
{
    int ar[20] ;
    int size ;
    cout<<"enter the size of array \n";
    cin>>size;
     cout<<"enter array element \n";
     cin>>ar[size];
    // cout<<"unsorted array is \n";
   // printArray(ar, size);
    heapSort(ar, size);
    cout<<"\nSorted array is \n";
    printArray(ar, size);
    return 0;
}

//Code written in Codeblocks

#include<iostream>
using namespace std;
int ctr,cmp_ctr;
void maxHeapify(int a[],int i,int n)
{
  int left=2*i+1;
  int right=2*i+2;
  int l=i;
  int temp;
  if((left<n) && (a[left]>a[i]))
    {
      l=left;
      cmp_ctr++;
    }
   if((right<n) && (a[right]>a[l]))
    {
      l=right;
      cmp_ctr++;
    }
  if(l != i)
    {
      temp=a[i];
      a[i]=a[l];
      a[l]=temp;
      ctr++;
      maxHeapify(a,l,n);
    }
}

main()
{
    int n;
    cout<<"\nEnter the number of elements: ";
    cin>>n;
    int array[n];
    cout<<"\nEnter the Elements of the array: ";

    for(int i=0; i<n; i++)
      cin>>array[i];
    
      ctr=0;
      for(int i=n/2; i>=0; i--)
        {
          maxHeapify(array,i,n);
        }
      cout<<"\nThe heap is: ";
      for(int i=0; i<n; i++)
       {
          cout<<array[i]<<"\t";
       }
      int size=n,temp;
      while(size != 1)
        {
            ctr=0;

          for(int i=size/2; i>=0; i--)
            maxHeapify(array,i,size);

          cout<<"\n\n\n\nHeap Array: ";
          for(int j=0; j<n; j++)
            {
              cout<<array[j]<<"\t";
            }
            cout<<"\n\n\tNo of swaps: "<<ctr<<"\n\tNo of comparisons: "<<cmp_ctr;
            cmp_ctr=0;
            temp=array[size-1];
            array[size-1]=array[0];
            array[0]=temp;
            size--;
        }

    cout<<"\n\nSorted Array: ";
      for(int i=0; i<n; i++)
          cout<<array[i]<<"\t";
}

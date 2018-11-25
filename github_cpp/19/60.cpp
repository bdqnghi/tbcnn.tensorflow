#include <stdio.h>

int Partition(int *A,int p,int r)
{
    int x=A[r];
    int i=p-1;
    int temp=0;
    for(int j=p;j<=(r-1);j++)
    {
        if(A[j]<=x)
        {
            i+=1;
            temp=A[i];
            A[i]=A[j];
            A[j]=temp;
        }
        
        
    }
     temp=A[i+1];
     A[i+1]=A[r];
     A[r]=temp;
     
    return i+1;
    
}

void Quicksort(int *A,int p,int r)
{
    int q=0;
    if(p<r)
    {
        q=Partition(A,p,r);
    
    
    Quicksort(A,p,q-1);
    Quicksort(A,q+1,r);
    }
}

int main()
{
   int A[9]={7,5,3,4,6,8,7,1,5};
   Quicksort(A,0,8);
   for(int i=0;i<9;i++)
   {
        printf("    %d\n", A[i]);
   }
    return 0;
}

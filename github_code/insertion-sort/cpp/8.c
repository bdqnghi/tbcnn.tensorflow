//Insertion Sort Algorithm
// Refer to the video of MyCodeSchool for understanding.

#include <iostream>
using namespace std;
void Insertion_sort(int A[], int n)
{
    int i,hole,tmp;
    for (i=1; i<n; i++) 
    {
        hole=i;
        while (hole>0 && A[hole-1] > A[hole]) 
        {
            tmp = A[hole];
            A[hole] = A[hole-1];
            A[hole-1] = tmp;
            hole--;
        }
    }
}

int main()
{
    int A[] = {4,6,3,10,5,9,2,8,1,12};
    Insertion_sort(A,10);
    for(int i=0;i<10;i++)
    	cout<<A[i]<<" ";
}


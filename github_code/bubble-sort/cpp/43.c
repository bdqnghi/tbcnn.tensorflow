#include <stdio.h>
#include <string.h>
#include <math.h>
int abs_compare(int a,int b)
{
    if (abs(a)>abs(b)) return 1;
    else return -1;
}
void bubblesort(int* A[],int n, int (*compare)(int,int))
{
    printf("Value of ptr in bubblesort = %d\n",compare);
    int i,j,temp;
    for (i=0;i<n;i++)
    {
        for (j=0;j<n-1;j++)
        {
            if (compare(*(A+j),*(A+j+1))>0)
            {
                temp = *(A+j);
                *(A+j) = *(A+j+1);
                *(A+j+1) = temp;
            }
        }
    }
}
int main()
{
    int i =0;
    int A[]={-31,22,-1,50,-6,4};
    printf("Value of ptr in main = %d\n",abs_compare);
    bubblesort(A,6,abs_compare);
    for (i=0;i<6;i++)
    {
        printf("%d\n",A[i]);
    }
}

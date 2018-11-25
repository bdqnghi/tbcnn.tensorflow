


#include<stdio.h>
#include<conio.h>
int* insertionsort(int arr[],int n)
{
	 int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;
 
        while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
   return arr;
		  }  	
	

int main()
{
	int a[20],n,i;
	printf("Enter the no of elements");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);
	int *p = insertionsort(a,n);
	for(i=0;i<n;i++)
	{
		printf("%d",*(p+i));
	}
}

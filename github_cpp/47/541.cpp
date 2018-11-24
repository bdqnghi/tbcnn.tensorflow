// binary-search
#include <stdio.h>
#define N 1000
int s[N]; 
int quicksort(int *arr,int left,int right);

int main(void)
{
	int i,j,n,x,k;
	printf("Please input the number of data\n");
	scanf("%d",&n);
	if (n<=0) {printf("error:input invalid");return 1;}
	printf("Please input the data\n");
	for (i=0;i<n;i++)
		scanf("%d",&s[i]);
	// input
	quicksort(s,0,n-1);
	//sort
	printf("Please input the data searched \n");
	scanf("%d",&x);
	i=0;j=n-1;
	do
	{
		k=(i+j)/2;
		if (s[k]>x) j=k-1;
		else if (s[k]<x) i=k+1;
	}
	while ((i<=j)&&(s[k]!=x));
	
	if (i<=j) printf("%d",k+1);
	else printf("Not found");
	//output
}

int quicksort(int *a,int l,int r)
{
	int i,j,key;
	
	if (l >=r ) return 0;
	i=l;j=r;key=a[i];
	while (i<j)
	{
		while ((i<j)&&(key<=a[j]))
			j--;
		a[i]=a[j];
		while ((i<j)&&(key>=a[i]))
			i++;
		a[j]=a[i];
	}
	a[i]=key;
	quicksort(a,l,i-1);
	quicksort(a,i+1,r);
	return 0;
}

#include <stdio.h>

void shellsort(int v[],int n);
void print(int v[]);
main()
{
	int v[]={9,2,3,5,4,9,4,5,20,3,4};
	print(v);
	printf("\n");
	shellsort(v,11);
	print(v);
	return 0;
}
void shellsort(int v[],int n)
{
	int i,j,temp,gap;
	
	for(gap=n/2;gap>0;gap/=2)
		for(i=gap;i<n;i++)
			for(j=i-gap;j>=0&&v[j]>v[j+gap];j-=gap)
			{
				printf("%d %d %d %d\n",j,j+gap,gap,i);
				temp=v[j];//binary sort
				v[j]=v[j+gap];//tim n/2 ssau do so sanh vi tri n/2 voi 0, 1voi n/2+1
				v[j+gap]=temp;
				print(v);
				printf("\n");
			}
}
void print(int v[])
{
	for(int i=0;i<11;i++)
		printf("%d ",v[i]);
}

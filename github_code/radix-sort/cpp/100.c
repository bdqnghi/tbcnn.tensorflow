#include "header.hpp"

int number(int, int, int);
void countsort(int *, int, int, int);

int main()
{
	int i, n, d;

	scanf("%d",&n);
	int *arr = new int[n];
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);

	d = digits(arr[0]);

	for(i=1;i<=d;i++)
		countsort(arr, i, d, n);

    for(i=0;i<n;i++)
        printf("%d\t",arr[i]);

    return 0;
}

void countsort(int *arr, int filter, int d, int n)
{
	int i;

	int max;
	max = number(arr[0], d, filter);
	for(i=1;i<n;i++)
		if(number(arr[i], d, filter)>max)
			max = number(arr[i], d, filter);

	int *aarr = new int[n];
	int count[max+1];
	memset(count, 0, sizeof(count));

    for(i=0;i<n;i++)
		count[number(arr[i], d, filter)]++;
	for(i=1;i<(max+1);i++)
        count[i] = count[i] + count[i-1];

	for(i=n-1;i>=0;i--)
		aarr[(count[number(arr[i], d, filter)]--)-1] = arr[i];

    for(i=0;i<n;i++)
		arr[i] = aarr[i];
}

int number(int temp, int digit, int filter)
{
	int tempp = temp%((int)pow(10,filter));
	tempp = tempp/((int)pow(10,filter-1));
	return tempp;
}

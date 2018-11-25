

#include <iostream>
#include <cstring>
using namespace std;


void bucketSort(int* a, int n, int max)
{
	int i, j;
    int *buckets;

    if (a==NULL || n<1 || max<1)
        return ;

    
    if ((buckets = new int[max])==NULL)
        return ;
    memset(buckets, 0, max*sizeof(int));

	
    for(i = 0; i < n; i++) 
        buckets[a[i]]++; 

	
	for (i = 0, j = 0; i < max; i++) 
		while( (buckets[i]--) >0 )
			a[j++] = i;

	delete[] buckets;
}


int main()
{
	int i;
	int a[] = {8,2,3,4,3,6,6,3,9};
	int ilen = (sizeof(a)) / (sizeof(a[0]));

	cout << "before sort:";
	for (i=0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	bucketSort(a, ilen, 10); 

	cout << "after  sort:";
	for (i=0; i<ilen; i++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}

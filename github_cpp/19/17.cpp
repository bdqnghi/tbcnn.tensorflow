

#include <algorithm>
using std::swap;

void sort(int *a, int n)
{
	
	if(n <= 1) return;
	if(n == 2)
	{
		if(a[0] > a[1]) swap(a[0], a[1]);
		return;
	}

	
	swap(a[0], a[n/2]);
	int key = a[0];

	
	int *L = a + 1;
	int *R = a + n -1;
	while(L < R)
	{
		while(L<R && *L < key) ++L;
		while(a<R && *R >= key) --R;
		if(L<R) swap(*L, *R);
	}

	
	if(*R < key) swap(a[0], *R);

	
	sort(a, R-a);
	sort(R+1, n-1-(R-a));
}


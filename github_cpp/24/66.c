#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

#define DEBUG

#define MAX(A, B) A > B ? : A > B

void swaper(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

int binary_search(int input[], int n, int handle, int lower_bound = 0, int upper_bound= -1)
{
	#ifdef DEBUG
		static int recursivecall = 0;
		recursivecall++;
		cerr << "Recusive Calls: " << recursivecall << endl;
	#endif

	if(input[lower_bound] == handle) return input[lower_bound];

	if(lower_bound == upper_bound)
		return -1;
	
	if(upper_bound == -1)
		upper_bound = n - 1;

	int midpoint = (lower_bound + upper_bound) / 2;

	if(input[midpoint] == handle) return input[midpoint];

	if(handle > input[midpoint])
		return binary_search(input, n, handle, midpoint + 1, upper_bound);
	else
		return binary_search(input, n, handle, lower_bound, midpoint);
}

int main(int argc, char const *argv[])
{
	int a[] = {5, 4, -20, 1, 4, 2, 8, -4, -1, 3, 7, 9, 13};

	
	for (int i = 0; i < sizeof(a)/sizeof(int); ++i)
	{

		int j = i + 1;
		int ii = i;

			while(j > 0)
			{
				if(a[j] > a[ii]){
					break;
				}
				swaper(a[j], a[ii]);
			j--;
			ii--;
			}
	}

	#ifdef DEBUG
		for (int i = 0; i < sizeof(a)/sizeof(int); ++i)
			cerr << a[i] << endl;
	#endif

		
		cout << binary_search(a, sizeof(a)/sizeof(int), 1) << endl;
	
	return 0;
}
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

/*
visualization:
https://www.cs.usfca.edu/~galles/visualization/BucketSort.html
*/

/* array elements lie in [-RANGE..RANGE) interval */
const double RANGE = (int)1e7;
const int NMAX = (int)1e6 + 5;

int arr[NMAX];

void bucket_sort(int *arr, int n)
{
	vector<int> b[n];

	for(int i = 0; i < n; i++) {
		int bi = (n * (1 + arr[i] / RANGE)) / 2;
		b[bi].push_back(arr[i]);
	}

	//sort individual buckets
	for(int i = 0; i < n; i++)
		sort(b[i].begin(), b[i].end());
	
	int index = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < b[i].size(); j++)
			arr[index++] = b[i][j];
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	
	bucket_sort(arr, n);

	for(int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}



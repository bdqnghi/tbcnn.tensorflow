
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>
#include <assert.h>

using namespace std;

int getMax(int x, int y) {
	if(x > y)
		return x;
	return y;
}

int debug = 1;
int find_max_benefit_subproblem(const int n, const int* const prices, int*localMaxes, const int from) {
	if(from >= n) // sanity check
		return 0;
	if(localMaxes[from] != -1)
		return localMaxes[from];
	int i = 0;
	int max = prices[n-from-1];
	if(debug)
		cout << "begining:" << from << ", max:" << max << endl;
	for(i = from+1; i < n; i++) {
		if(debug)
			cout << "we cut it at " << i << endl;
		max = getMax(max, find_max_benefit_subproblem(n, prices, localMaxes, i) + prices[i-from-1]);
	}
	if(debug)
		cout << "ending:" << from << ", max:" << max << endl;
	localMaxes[from] = max;
	if(debug) {
		for(i = 0; i < n; i++) {
			cout << localMaxes[i] << ',';
		}
		cout << endl;
	}
	return max;
}

int find_max_benefit_top_down(const int n, const int* const prices) {
	int localMaxes[n];
	for(int i=0; i < n; i++) {
		localMaxes[i] = -1;
	}
	return find_max_benefit_subproblem(n, prices, localMaxes, 0);
}

int find_max_benefit_bottom_up(const int n, const int* const prices) {
	int localMaxes[n];
	int cuts[n];
	localMaxes[0] = prices[0];
	cuts[0] = 0;
	for(int i=1; i < n; i++) {
		int max = prices[i];
		cuts[i] = i;
		for(int j = 1; j < i; j++) {
			if(max < localMaxes[i-j-1]+prices[j]) {
				cuts[i] = j;
				max = localMaxes[i-j-1]+prices[j];
			}
		}
		localMaxes[i] = max;
		if(debug)
			cout << "max " << (i+1) << " : " << max << endl;
	}
	if(debug) {
		for(int i = 0; i < n; i++) {
			cout << (i+1) << " length cuts at " << (cuts[i]+1)  << " to get " << localMaxes[i] << endl;
		}
	}
	return localMaxes[n-1];
}


int find_max_benefit(const int n) {
	int prices[n];
	int i = n;
	// read the prices
	for(i=0; i < n; i++) {
		cin >> prices[i];
	}
	// find max benefit 
	int top_down_max = find_max_benefit_top_down(n, prices);
	int bottom_up_max = find_max_benefit_bottom_up(n, prices);
	cout << bottom_up_max << endl;
	assert(top_down_max == bottom_up_max);
	return top_down_max;
}

int main(int argc, char*argv[]) {
	/* n is the length of the rod */
	int n; 
	cin >> n; 
	cout << find_max_benefit(n) << endl;
	return 0;
}


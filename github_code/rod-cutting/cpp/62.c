#include <iostream>
#include <climits>
using namespace std;

/**
 * Implemented using dynamic programming. Bottom up approach.
 * @len array of lengths
 * @p array of prices of the corresponding length
 * @t_len total length of the rod
 */
int rodCuttingDP(int len[], int p[], int n, int t_len) {
	int max_price[t_len+1];
	max_price[0] = 0;
	for(int i=1; i<=t_len; i++) {
		int max_val = INT_MIN;
		for(int j=0; j<n; j++) {
			if(i-len[j] >= 0)
				max_val = max(max_val, p[j]+max_price[i-len[j]]);
			else
				max_val = max(max_val, max_price[i-1]);
		}
		max_price[i] = max_val;
	}
	// for(int i=0; i<=t_len; i++)
	// 	cout << max_price[i] << ", ";
	// cout << endl;
	return max_price[t_len];
}

/**
 * Implemented using dynamic programming. Bottom up approach.
 * @len array of lengths
 * @p array of prices of the corresponding length
 * @t_len total length of the rod
 */
int rodCuttingNaive(int len[], int p[], int n, int t_len) {
	// Not a correct approach as repetitve case are not taken into consideration
	// by the following algorithm.
	// if(t_len == 0 || n == 0)
	// 	return 0;
	// else if(t_len-len[n-1] >= 0)
	// 	return max(rodCutting(len, p, n-1, t_len),
	// 		p[n-1]+rodCutting(len, p, n-1, t_len-len[n-1]));
	// else
	// 	return rodCutting(len, p, n-1, t_len);

	// Correct Implementation
	int max=0;
	for(int i=0; i<n; i++) {
		if(t_len-len[i] >= 0) {
			int temp = p[i]+rodCuttingNaive(len, p, n, t_len-len[i]);
			if(temp > max) max = temp;
		}
	}
	return max;
}

int main() {
	// int len[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	// int p[] = {1, 5, 8, 9, 10, 17, 17, 20, 56, 34, 5, 7, 21};
	// cout << rodCuttingNaive(len, p, 13, 13) << endl;
	// cout << rodCuttingDP(len, p, 13, 13) << endl;
	int len[] = {1, 2, 3, 4, 5};
	int p[] = {3, 5, 10, 12, 14};
	cout << rodCuttingDP(len, p, 5, 5) << endl;
	return 0;
}
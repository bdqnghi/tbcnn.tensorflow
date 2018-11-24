/*
 * Author:		Ashish Verma
 * Title:		rod cutting problem
 *
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>

#define debug(x) cout << "DEBUG: " << x << endl
#define INFINITE 99999

using namespace std;

int maxRodPrice(int price[], int maxL) {
	int dp[maxL + 1];
	dp[0] = 0;

	for (int i = 1; i <= maxL; i++) {
		int maxPrice = INT_MIN;
		for (int j = 1; j <= i; j++) {
			maxPrice = max(maxPrice, price[j - 1] + dp[i - j]);
		}
		dp[i] = maxPrice;
	}
	return dp[maxL];
}

int main() {

	int ar[] = { 1, 5, 8, 9, 10, 17, 17, 20 };
	int n = sizeof(ar) / sizeof(ar[0]);

	cout << maxRodPrice(ar, n);

	return 0;
}

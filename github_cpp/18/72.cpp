#include <iostream>
using namespace std;

int dp[100];
int maxCost;

int maxCostDp(int cost[], int length) {
	if(dp[length] != -1) {
		return dp[length];
	}
	int maxm = cost[length];
	for(int i = 1; i <= length/2; i++) {
		maxm = max(maxm, maxCostDp(cost, length - i) + maxCostDp(cost, i));
	}
	dp[length] = maxm;
	return dp[length];
}

int main() {
	int n;
	int cost[100];
	cin >> n;
	cost[0] = 0;
	dp[0] = 0;
	for(int i = 1; i <= n; i++) {
		cin >> cost[i];
		dp[i] = -1;
	}
	int maxCost = maxCostDp(cost, n);
	cout << maxCost << endl;
}
// 2017029807_��âȣ_12525

#include<bits/stdc++.h>
using namespace std;

int n, v[101], dp[101], path[101];
vector<int> ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &v[i]);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (dp[i] < dp[i - j] + v[j]) {
				dp[i] = dp[i - j] + v[j];
				path[i] = j;
			}
		}
	}

	printf("%d\n", dp[n]);
	while (n) {
		ans.push_back(path[n]);
		n -= path[n];
	}
	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);

	return 0;
}
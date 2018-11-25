

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int p[101];
int dp[101];
int s[101];

int Rodcutting(int n) {
	int num;

	for (int i = 1; i <= n; ++i) {
		scanf("%d", &num);
		p[i] = num;
	}
	int q;
	for (int j = 1; j <= n; ++j) {
		q = INT_MIN;
		for (int i = 1; i <= j; ++i) {
			if (q < p[i] + dp[j - i]) {
				q = p[i] + dp[j - i];
				s[j] = i;
			}
		}
		dp[j] = q;
	}
	return dp[n];
}


int main(void) {
	int n;
	scanf("%d", &n);
	printf("%d\n", Rodcutting(n));
	
	while (n > 0) {
		printf("%d ", s[n]);
		n = n - s[n];
	}
	return 0;
}
//2013012085_������_A
//Rodcutting.cpp

#include <stdio.h>
#include <algorithm>

using namespace std;
int p[111];
int N;
int dp[111];
int q;
int back[111];
int rod_cut(int r) {
	if (dp[r] >= 0) {
		return dp[r];
	}
	if (r == 0) {
		q = 0;
	}
	else {
		q = -987654321;
		for (int j = 1;j <= r;j++) {
			int temp = p[j] + rod_cut(r - j);
			if (q < temp) {
				q = temp;
				back[r] = j;
			}
		}
		dp[r] = q;
	}
	return q;
}
int main() {
	scanf("%d", &N);
	for (int i = 1;i <= N;i++) {
		scanf("%d", &p[i]);
		dp[i] = -987654321;
	}
	printf("%d\n", rod_cut(N));

	while (N > 0) {
		printf("%d ", back[N]);
		N = N - back[N];
	}
	return 0;
}

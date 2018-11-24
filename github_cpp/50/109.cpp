#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
#pragma warning(disable:4996)
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m;
	cin >> n >> m;
	vector<int> v0(m + 1);
	vector<vector<int>> ruk(n + 1, v0);
	vector<int> w(n);
	vector<int> p(n);
	for (int i = 0; i < n; i++) {
		cin >> w[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}

	for (int i = 1; i < n + 1; i++) {
		ruk[i] = ruk[i - 1];
		for (int j = m; j >= w[i - 1]; j--) {
			if (ruk[i][j] < ruk[i][j - w[i - 1]] + p[i - 1]) {
				ruk[i][j] = ruk[i][j - w[i - 1]] + p[i - 1];
			}
		}
	}
	int j = m;
	for (int i = n; i >= 1; i--) {
		if (ruk[i][j] != ruk[i - 1][j]) {
			j = j - w[i - 1];
			cout << i << ' ';
		}
	}
}
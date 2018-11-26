#include <bits/stdc++.h>

// lev-dist.cpp
// author: Seong Yong-ju ( @sei40kr )
// Copyright (c) 2017 Seong Yong-ju

#define FOR(i, a, b) for (int(i) = (a); i < (b); ++i)

using namespace std;

int lev_dist(const string &s1, const string &s2) {
  const size_t n = s1.size(), m = s2.size();
  int dp[n + 1][m + 1];

  fill((int *)(&dp[0]), (int *)(&dp[0]) + (n + 1) * (m + 1), 0);
  FOR(i, 1, n + 1) { dp[i][0] = i; }
  FOR(j, 1, m + 1) { dp[0][j] = j; }

  FOR(j, 1, m + 1) {
    FOR(i, 1, n + 1) {
      dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1,
                      dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1)});
    }
  }

  return dp[n][m];
}

int main() {
  ios::sync_with_stdio(false);

  cout << lev_dist("kitten", "sitting") << endl;
  cout << lev_dist("Saturday", "Sunday") << endl;
}

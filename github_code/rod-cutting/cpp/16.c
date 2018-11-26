// clang-format off
// https://leetcode.com/problems/integer-break/description/
// DP: rod-cutting, backpack
// input: n
// state def:
// s(i) = maximize the product of at least two positive integers which sum up to n
// state init:
// s(1) = 1
// state transition:
// s(i) = max{j = 1..i / 2}{max(j, s(j)) * max(i - j, s(i - j))}
// output:
// s(n)
// Time Complexity: O(n^2)
// Space Complexity: O(n)
// clang-format on

class Solution {
 public:
  int integerBreak(int n) {
    if (n <= 0) { return 0; }

    vector<int> s(n + 1, 0);

    // init
    s.at(1) = 1;

    // iteration
    for (int i = 2; i <= n; i++) {
      for (int j = 1; j <= i / 2; j++) {
        s.at(i) = max(s.at(i), max(j, s.at(j)) * max(i - j, s.at(i - j)));
      }
    }

    return s.at(n);
  }
};

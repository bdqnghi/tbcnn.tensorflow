















class Solution {
 public:
  int integerBreak(int n) {
    if (n <= 0) { return 0; }

    vector<int> s(n + 1, 0);

    
    s.at(1) = 1;

    
    for (int i = 2; i <= n; i++) {
      for (int j = 1; j <= i / 2; j++) {
        s.at(i) = max(s.at(i), max(j, s.at(j)) * max(i - j, s.at(i - j)));
      }
    }

    return s.at(n);
  }
};

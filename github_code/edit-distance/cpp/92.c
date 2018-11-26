#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class LevenshteinDistance {
 public:
  // The strings must be 0 indexed.
  LevenshteinDistance(const string& a, const string& b) : a_(a), b_(b) {
    dp_ = vector<vector<int>>(a.size() + 1, vector<int>(b.size() + 1, kInf));
  }

  int FindDistance() {
    for (int i = 0; i <= (int)a_.size(); i++) {
      dp_[i][0] = i;
    }
    for (int i = 0; i <= (int)b_.size(); i++) {
      dp_[0][i] = i;
    }

    for (int i = 1; i <= (int)a_.size(); i++) {
      for (int j = 1; j <= (int)b_.size(); j++) {
        dp_[i][j] = dp_[i - 1][j] + 1;
        dp_[i][j] = min(dp_[i][j], dp_[i][j - 1] + 1);
        dp_[i][j] = min(dp_[i][j], dp_[i - 1][j - 1] + (a_[i - 1] != b_[j - 1]));
      }
    }

    return dp_[a_.size()][b_.size()];
  }

 private:
  static const int kInf = numeric_limits<int>::max();
  const string a_;
  const string b_;
  vector<vector<int>> dp_;
};

int main() {
  cin.sync_with_stdio(false);

  string a;
  cin >> a;

  string b;
  cin >> b;

  LevenshteinDistance ld(a, b);
  cout << ld.FindDistance() << '\n';

  return 0;
}

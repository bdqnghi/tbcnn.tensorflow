#include <iostream>
#include <vector>
using namespace std;

int tam;
vector<int> prices;
vector<int> memo;

int max(int a, int b) {
  return (a > b)? a : b;
}

int eval(int sz, int total) {
  int best;

  if (memo[sz] > 0)
    best = memo[sz];
  else if (sz == 0)
    best = total + prices[0];
  else for (int i = 0; i < sz; ++i)
    best = max(prices[sz], prices[i] + eval(sz-i-1, total));

  return best;
}


int main() {
  int i, j;
  int outlet;

  while (cin >> tam) {
    
    prices.clear();
    memo.clear();
    for (i = 0; i < tam; ++i) {
      cin >> j;
      prices.push_back(j);
      memo.push_back(-1);
    }

    
    memo[0] = prices[0];
    outlet = -1;
    for (i = 0; i < tam; ++i)
      outlet = max(outlet, eval());

    
    cout << outlet << endl;
  }

  return 0;
}

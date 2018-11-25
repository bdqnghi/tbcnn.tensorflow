

#include <iostream>
using namespace std;
typedef long long LL;

LL i, j, k;
LL N, M;
LL price[100009], length[100009], dp[100009];

int main(){
  cin >> N >> M;
  for(i = 0; i < M; ++i){
    cin >> length[i];
  }
  for(i = 0; i < M; ++i){
    cin >> price[length[i]];
  }

  length[0] = 0;
  price[0] = 0;
  dp[0] = 0;
  for(i = 1; i < N; ++i){
    for(j = 0; j < i; ++j){
      if(dp[i-j] + price[j] > dp[i]){
	dp[i] = dp[i-k] + price[j];
      }
    }
  }

  cout << dp[N] << endl;
}

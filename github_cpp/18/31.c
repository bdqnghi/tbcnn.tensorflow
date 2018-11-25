

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;


int lengthOfRod = 5;
int prices[5] = {0, 2, 5, 7, 3};
int dp[6][6]; 

void solve(){
  for(int i = 1;  i < sizeof(prices)/sizeof(prices[0]); i ++){
    for(int j = 1; j <= lengthOfRod; j ++){
      if(i <= j){
        
        dp[i][j] = max(dp[i - 1][j], prices[i] + dp[i - 1][j - 1]);
      }else{
        
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
}

void showResult(){
  cout << "Maximum profit: " + dp[sizeof(prices)/sizeof(prices[0]) - 1][lengthOfRod] << endl;
  
  int n;
  int w;
  for(n = sizeof(prices)/sizeof(prices[0]) - 1; w = lengthOfRod; n > 0){
    if(dp[n][w] != 0 && dp[n][w] != dp[n - 1][w]){
      cout << "Make cut: " + n << endl;
      w -= n;
    }else{
      n --;
    }
  }
}

int main(){
  solve();
  showResult();
}

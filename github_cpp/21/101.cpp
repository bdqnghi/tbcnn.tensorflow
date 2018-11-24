#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<cmath>
#include<set>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#define MAX 100001
#define ll long long int
#define eps 1e-7
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
      int n = word1.size();
      int m = word2.size();
      int dp[n+1][m+1];
      for(int i=0;i<m;i++){
        dp[0][i] = i;
      }
      for(int i=0;i<n;i++){
        dp[i][0] = i;
      }
      for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
          if(word1[i-1]==word2[j-1]){
            dp[i][j] = dp[i-1][j-1];
          }
          else {
            dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
          }
        }
      }
      return dp[n-1][m-1];
    }
};

string word1,word2;
int main(){
  Solution sol;
  cin>>word1;
  cin>>word2;
  cout<<sol.minDistance(word1,word2)<<endl;
  return 0;
}

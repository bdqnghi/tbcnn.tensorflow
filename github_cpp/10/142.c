#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int dp[2001][2001];

int main(){
    string s1,s2;
    int t;
    cin>>t;
    while(t--){
    cin>>s1>>s2;
    int l1,l2;
    l1=s1.size();
    l2=s2.size();
    for(int i=0;(i<=l1||i<=l2);++i){
        dp[i][0]=dp[0][i]=i;
    }

    for(int i=1;i<=l1;++i){
        for(int j=1;j<=l2;++j){
            int mini=3000;
            mini=min(mini,(dp[i-1][j-1]+(s1[i-1]==s2[j-1]?0:1)));
            mini=min(mini,dp[i-1][j]+1);
            mini=min(mini,dp[i][j-1]+1);
            dp[i][j]=mini;
        }
    }
    cout<<dp[l1][l2]<<endl;
    }
return 0;}

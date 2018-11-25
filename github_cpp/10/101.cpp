#include <bits/stdc++.h>
using namespace std;

int LD(const string& source, const string& target){
    int dp[source.size()+1][target.size()+1];

    for(int i=0; i<=source.size(); i++){
        dp[0][i] = i;
    }

    for(int i=0; i<=target.size(); i++){
        dp[i][0] = i;
    }

    for(int i=0; i<source.size(); i++){
        for(int j=0; j<target.size(); j++){
            int edit = 1;
            if(source[i]==target[i]) edit = 0;
            dp[i+1][j+1] = min(dp[i][j]+edit, min(dp[i][j+1]+1, dp[i+1][j]+1));
        }
    }

    return dp[source.size()][target.size()];
}

int main(){
    string s, t;

    while(cin>>s>>t){
        cout<<"Lavenshtein distance between "<<s<<" and "<<t<<" is "<<LD(s, t)<<endl;
    }

    return 0;
}

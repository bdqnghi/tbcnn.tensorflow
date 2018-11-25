#include <bits/stdc++.h>
using namespace std;

char a[2001];
char b[2001];

int dp[2001][2001];

int levDist(char s1[], char s2[]){
	
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	int i,j;

	for(i = 0; i<=len1; i++){
		dp[0][i] = i;
	}

	for(i = 0; i<=len2; i++){
		dp[i][0] = i;
	}

	for(i = 1; i<=len1; i++){
		for(j = 1; j<=len2; j++){
			if(s1[i-1] == s2[j-1]){
				dp[j][i] = dp[j-1][i-1];
			}else{
				dp[j][i] = min(dp[j-1][i] + 1, min(dp[j][i-1] + 1, dp[j-1][i-1] + 1));
			}
		}
	}

	return dp[len2][len1];
}

int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>a>>b;
		cout<<levDist(a, b)<<endl;
	}
	return 0;
}

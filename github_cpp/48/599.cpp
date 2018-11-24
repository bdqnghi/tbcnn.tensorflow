#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#ifdef PAPITAS
	#define DEBUG 1
#else
	#define DEBUG 0
#endif
#define _DO_(x) if(DEBUG) x

int main()
{
	#ifdef PAPITAS
		freopen("in.txt","r",stdin);
		freopen("out.txt","w",stdout);
	#endif
	int T;
	cin >> T;
	string s;
	getline(cin,s);
	while(T--){
		getline(cin, s);
		int n = s.size();
		//cout << n << '\n';
		//cout << s << '\n';
		int dp[n+1][n+1];
		memset(dp, 0, sizeof(dp));
		for(int i = 1; i <= n; i++) dp[i][i] = 1;
		for(int i = 2; i <= n; i++){
			for(int j = i-1; j >= 1; j--){
				dp[j][i] = max(dp[j][i-1], dp[j+1][i]);
				if(s[i-1] == s[j-1]){
					dp[j][i] = max(dp[j][i], dp[j+1][i-1] + 2);
				}
			}
		}
		/*
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				cout << dp[i][j] << ' ';
			}
			cout << '\n';
		}
		*/
		cout << dp[1][n] << '\n';
	}
	return 0;
}


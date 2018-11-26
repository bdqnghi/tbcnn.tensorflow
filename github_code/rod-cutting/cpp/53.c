/**

https://practice.geeksforgeeks.org/problems/rod-cutting/0/

**/
#include <iostream>
using namespace std;

int max(int a, int b){
    return (a > b) ? a : b;
}
int main() {
	//code
	int t;
	cin>>t;
	while(t--){
	    int n; 
	    cin>>n;
	   // cout<<n;
	    int arr[n];
	    for(int i =0 ; i < n; i++) {
	        cin>>arr[i];
	        
	    }
	    int dp[n+1][n+1];
	    for( int i = 0; i <= n; i++ ) {
	        dp[i][0] = 0;
	        dp[0][i] = 0;
	    }
	    for( int i = 1; i <= n; i++ ) {
	       // cout<<arr[i-1]<<",";
	         for( int j = 1; j <= n; j++ ) {
	             if(j < i) {
	                 dp[i][j] = dp[i-1][j];
	             } else {
	                 dp[i][j] = max(dp[i][j-i]+arr[i-1], dp[i-1][j]);
	             }
	         }
	    }
	    cout<<dp[n][n]<<endl;
	    
	}
	return 0;
}
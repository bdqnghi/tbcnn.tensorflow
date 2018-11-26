/*
Time : Fri Sep 01 2017 10:28:12 GMT+0530 (IST)
URL : http://practice.geeksforgeeks.org/problems/rod-cutting/0
Given a rod of length n inches and an array of prices that contains prices of all pieces of size 
smaller than n. Determine the maximum value obtainable by cutting up the rod and selling the pieces.

Input:
First 
line consists of T test cases. First line of every test case consists of N, denoting the size of 
array. Second line of every test case consists of price of ith length piece.

Output:
Single line 
output consists of maximum price obtained.

Constraints:
1<=T<=100
1<=N<=100
1<=Ai<=100

Example:
Input:
1
8
1 
5 8 9 10 17 17 20
Output:
22

**For More Examples Use Expected Output**

*/

#include <bits/stdc++.h>

using namespace std;

int solve(std::vector<int> v){
	int n = v.size();
	std::vector<int> maxi(n);
	maxi[1] = v[1];
	for(int i=2;i<n;i++){
		maxi[i] = v[i];
		for(int j=i-1;j>=1;j--){
			maxi[i] = max( maxi[i], maxi[i-j] + maxi[j]);
		}
	}
	return maxi[n-1];
}

int main() {
	int t;
	cin >> t;
	while(t--){
	    int n;
	    cin >> n;
	    vector<int> value(n+1);
	    for(int i=1;i<=n;i++){
            cin >> value[i];
        }
        cout << solve(value) << endl;
	}
	return 0;
}
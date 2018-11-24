#include <iostream>
#include <fstream>

using namespace std;

ifstream fi("Palindrome.inp");

const int MN = 1010;
int n;
char s[MN];

int input() {
	string temp;
	fi >> temp;
	n = temp.length();
	for (int i=0; i<n; i++) {
		s[i] = temp[i];
	}
//	for (int i=0; i<n; i++) {
//		cout << s[i];
//	}
}

int max(int a, int b) {
	return (a>b)? a:b;
}
int d = 0;

int solve(int i, int j) {
	d++;
	if(i > j) return 0;
	if(i == j) return 1;
	if(s[i] == s[j]) return solve(i+1, j-1) + 2;
	return max( solve(i+1,j) , solve(i,j-1) );
}

int solveB() {
}

main() {
	input();
	cout << solve(0, n-1) << endl;
	cout << d << endl;
}

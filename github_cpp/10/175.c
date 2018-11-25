#include <iostream>
using namespace std;

int editDistance(string s, string t) {
	
	if(s.size() == 0 || t.size() == 0) {
		return max(s.size(), t.size());
	}


	if(s[0] == t[0]) {
		return editDistance(s.substr(1), t.substr(1));
	}
	else {
		
		int x = editDistance(s.substr(1), t) + 1;
		
		int y = editDistance(s, t.substr(1)) + 1;
		
		int z = editDistance(s.substr(1), t.substr(1)) + 1;

		return min(x, min(y, z));
	}
}

int main() {
	string s = "abcdf";
	string t = "afd";
	
	cout << editDistance(s, t) << endl;
}




#include <iostream>
using namespace std;


int editDistance(string s, string t) {
	
	if(s.size() == 0 || t.size() == 0) {
		return max(s.size(), t.size());
	}


	if(s[0] == t[0]) {
		return editDistance(s.substr(1), t.substr(1));
	}
	else {
		
		int x = editDistance(s.substr(1), t) + 1;
		
		int y = editDistance(s, t.substr(1)) + 1;
		
		int z = editDistance(s.substr(1), t.substr(1)) + 1;

		return min(x, min(y, z));
	}
}


int editDistance_DP(string s, string t) {
	int m = s.size();
	int n = t.size();
	int **ans = new int*[m+1];
	for(int i = 0; i <= m; i++) {
		ans[i] = new int[n+1];
	}
	for(int j = 0; j <= n; j++) {
		ans[0][j] = j;
	}

	for(int i = 0; i <= m; i++) {
		ans[i][0] = i;
	}

	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {
			if(s[m-i] == t[n-j]) {
				ans[i][j] = ans[i-1][j-1];
			}
			else {
				ans[i][j] = min(ans[i-1][j], min(ans[i][j-1], ans[i-1][j-1])) + 1;
		
			}
		}

	}
	return ans[m][n];

}








int editDistance_Better(string s, string t, int **ans) {
	if(s.size() == 0 || t.size() == 0) {
		return max(s.size(), t.size());
	}

	int m = s.size();
	int n = t.size();

	if(ans[m][n] != -1) {
		return ans[m][n];
	}

	if(s[0] == t[0]) {
		ans[m][n] = editDistance(s.substr(1), t.substr(1));
	}
	else {
		ans[m-1][n] = editDistance(s.substr(1), t);
		ans[m][n-1] = editDistance(s, t.substr(1));
		ans[m-1][n-1] = editDistance(s.substr(1), t.substr(1));

		ans[m][n] = 1 + min(ans[m-1][n], min(ans[m][n-1], ans[m-1][n-1]));
	}
	return ans[m][n];

}










































int editDistance_Better(string s, string t) {
	int m = s.size();
	int n = t.size();
	int **ans = new int*[m+1];
	for(int i = 0; i <= m; i++) {
		ans[i] = new int[n+1];
		for(int j = 0; j <= n; j++) {
			ans[i][j] = -1;
		}
	}
	return editDistance_Better(s, t, ans);

}

int main() {
	string s = "abcdf";
	string t = "afd";
	
	cout << editDistance_Better(s, t) << endl;
	cout << editDistance(s, t) << endl;
}

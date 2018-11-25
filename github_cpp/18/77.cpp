

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
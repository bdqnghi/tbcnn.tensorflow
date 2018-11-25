#include <iostream>
#include <climits>
using namespace std;


int rodCuttingDP(int len[], int p[], int n, int t_len) {
	int max_price[t_len+1];
	max_price[0] = 0;
	for(int i=1; i<=t_len; i++) {
		int max_val = INT_MIN;
		for(int j=0; j<n; j++) {
			if(i-len[j] >= 0)
				max_val = max(max_val, p[j]+max_price[i-len[j]]);
			else
				max_val = max(max_val, max_price[i-1]);
		}
		max_price[i] = max_val;
	}
	
	
	
	return max_price[t_len];
}


int rodCuttingNaive(int len[], int p[], int n, int t_len) {
	
	
	
	
	
	
	
	
	

	
	int max=0;
	for(int i=0; i<n; i++) {
		if(t_len-len[i] >= 0) {
			int temp = p[i]+rodCuttingNaive(len, p, n, t_len-len[i]);
			if(temp > max) max = temp;
		}
	}
	return max;
}

int main() {
	
	
	
	
	int len[] = {1, 2, 3, 4, 5};
	int p[] = {3, 5, 10, 12, 14};
	cout << rodCuttingDP(len, p, 5, 5) << endl;
	return 0;
}
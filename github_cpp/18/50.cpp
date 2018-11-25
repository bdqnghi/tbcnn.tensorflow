

#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<utility>

using namespace std;


typedef vector <int> profits;



void input (profits &arr) {
	for(auto &i : arr) {
		cin >> i;
	}
}
void output(profits arr) {
	for(auto i : arr)
	cout << i << " ";
	cout << endl;
}


void rod_cutting (profits &arr) {
	int m;
	for(auto i = 0 ; i < arr.size() ; i ++) {
		m = arr[i];
		for(auto j = i-1 ; j >= 0 ; j --) {
			m = max(m , arr[j]+arr[i-j-1]);	
		}
		arr[i] = m ;	
	}	
}

main() {
	int test;
	cin >> test;
	while(test--) {
		int rod_length;
		cin >> rod_length;
		profits arr(rod_length);
		input(arr);
		rod_cutting(arr);
		output(arr);
	}
}


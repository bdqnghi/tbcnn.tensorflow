

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "sort.h"

using namespace std;

pair< vector<int>, vector<int> > rodCutting(int profit[], int n){
	vector<int> R(n);
	vector<int> C(n);

	
	R[0] = 0;

	
	for(int i=0;i<n;i++){
		R[i] = profit[1] + R[i-1];
		C[i] = 1;
		for(int j=1;j<=i;j++){
			if(R[i] < R[i-j] + profit[i]){
				R[i] = profit[j] + R[i-j];
				C[i] = j;
			}
		}
	}

	return {R, C};
}

int main(){
	
	int n, k;
	
	cin >> n;
	int A[n];

	k=n;

	srand(time(NULL));

	cout << "Profits:" << endl;

	while(k--){
		A[n-k] = rand() % 50+1;
		
	}

	*A = merge_sort(A, 0, n);

	for(int i=0;i<n;i++){
		cout << i << " : " << A[i] << endl;
	}

	auto ret = rodCutting(A, n);

	vector<int> R = ret.first;
	vector<int> C = ret.second;

	cout << "Maximum Profit Achieved: " << R[n-1] << endl;
	cout << "Places to cut: " << endl;
	int i = n-1;
	while(i>0){
		cout << C[i] << endl;
		i = i - C[i];
	}

	return 0;

}
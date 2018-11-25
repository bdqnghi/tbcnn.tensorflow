

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "sort.h"

using namespace std;

pair< vector<float>, vector<float> > rodCuttingMemoized(float profit[], int n){
	vector<float> R(n);
	vector<float> C(n);

	float cost = (1.0/float(n));

	cout << "Cost per action: " << cost << endl;

	
	R[0] = 0.0;

	
	for(int i=1;i<=n;i++){
		R[i] = profit[1] + R[i-1] - cost;
		C[i] = 1;
		if(i==n){
			R[i] = profit[i];
			C[i] = n;
		}
		for(int j=2;j<=i;j++){
			if(R[i] < R[i-j] + profit[i] - cost){
				R[i] = profit[j] + R[i-j] - cost;
				C[i] = j;
			}
		}
	}

	return {R, C};
}

int main(){
	
	int n, k;
	cin >> n;
	float A[n];

	k=n;

	srand(time(NULL));

	cout << "Profits:" << endl;

	while(k--){
		A[n-k] = rand() % 50+1;
		
	}

	*A = merge_sort(A, 1, n+1);

	for(int i=1;i<=n;i++){
		cout << i << " : " << A[i] << endl;
	}

	auto ret = rodCutting(A, n);

	vector<float> R = ret.first;
	vector<float> C = ret.second;

	cout << "Maximum Profit Achieved: " << int(round(R[n])) << endl;
	cout << "Lengths to cut: " << endl;
	float i = n;
	while(i>0){
		cout << C[i] << endl;
		i = i - C[i];
	}

	return 0;

}
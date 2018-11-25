/*
 * BucketSort.cpp
 *
 *  Created on: 08-Jul-2018
 *      Author: Sahil S
 */

// Sort floating point numbers uniformly distributed between range 0.0 and 1.0
// Time Complexity : O(n)

#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

void bucketSort(float arr[], int n){
	vector<float> b[n];
	int i;
	for (i=0;i<n;i++){
		int bi = n*arr[i];
		b[bi].push_back(arr[i]);
	}
	for(i =0 ;i <n ;i++)
		sort(b[i].begin(), b[i].end());

	int index = 0;
	for(i = 0;i<n;i++)
		for(int j = 0;j<b[i].size();j++)
			arr[index++] = b[i][j];
}

int main(){
	float arr[] ={0.897,0.798,0.65,0.12,0.25,0.43,0.39};
	int n = 7;
	bucketSort(arr, n);
	printf("Sorted Array \n");
	for (int i = 0;i<n;i++)
		printf("%f ",arr[i]);

	return 0;
}

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;



void bucketSort (int arr[], int n){
	int m = 1000001;
	int* buckets = new int[m];
	for (int i = 0; i < m; ++i)
		buckets[i] = 0;
	for (int i = 0; i < n; ++i)
		++buckets[arr[i]];
	for (int i = 0, j = 0; j < m; ++j)
		for (int k = buckets[j]; k > 0; --k)
			arr[i++] = j;
	delete[] buckets;
}

void runBucket(int array[], int n, const char nombre[]){
	float startTime, endTime;
	startTime = ((float)clock())/CLOCKS_PER_SEC;
	bucketSort(array, n);
	endTime = ((float)clock())/CLOCKS_PER_SEC;
	float timeDiff = endTime-startTime;
	cout << "The bucket-sort algorithm took approximately " << timeDiff << " seconds to execute." << endl;
	ofstream myfile2(nombre);
	for(int i = 0; i < 1000000 ; i++){
		if (myfile2.is_open()){
   			myfile2 << array[i] << '\n';
    	}
	}
	myfile2.close();
}

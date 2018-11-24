#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include "../../common/timer.h"

using namespace std;

int main(int argc, char *argv[])
{
	Timer timer;
	vector<int> v;
	if (argc != 2) {
		cout << "\"" << argv[0] << " [int]\"" << endl;
		return 0;
	}
	int size = atoi(argv[1]);
	cout << "data_size=" << size << endl;
	
	timer.Start();
	v.resize(size);
	freopen("data.in", "r", stdin);
	for (int i=0; i<size; i++){ 
		cin >> v[i];
	}
	cout << endl;
	timer.Stop();
	cout << "read data cost " << timer.GetElapsedMillseconds() << "ms" << endl;
	
	timer.Start();
	vector<set<int>> bucket;
	int bucket_count = size/10;
	bucket.resize(bucket_count);
	for (auto &i : v) {
		bucket[i/bucket_count].insert(i);
	}
	timer.Stop();
	cout << "cost time " << timer.GetElapsedMillseconds() << "ms" << endl;
	cout << "cost zone " << bucket.size()* << endl;
}


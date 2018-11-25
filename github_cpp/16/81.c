

#include <vector>
#include <iostream>
#include <utility>

using namespace std;

vector<int>  shellSort(vector<int> vec) {
	cout << "using shellsort.." << endl;
	
	int numPasses = 0;
	for (int gap = vec.size() / 2; gap > 0; gap /= 2) {
		++numPasses;
		for (int i = gap; i < vec.size(); i++) {
			int temp = vec[i];
			int j = i;
			for ( ; j >= gap && temp < vec[j - gap ]; j -= gap) {
				vec[j] = vec[j - gap];
			}
			vec[j] = temp;
		}
		
	}	
	return vec;

}  




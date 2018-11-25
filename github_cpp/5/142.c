

#include <vector>
#include <iostream>
#include <utility>

using namespace std;

vector<int>  insertionSort(vector<int> vec) {
	cout << "using insertion sort..." << endl;
	
	for (int i = 1; i < vec.size(); i++) {
		int temp = (vec[i]);		
		int j;
		for (j = i; j > 0 && temp < vec[j - 1]; j--) {
			int temp2 = vec[j - 1];
			vec[j] = temp2;
		}
		vec[j] = temp;
		
		
		
	}	
	return vec;

}  





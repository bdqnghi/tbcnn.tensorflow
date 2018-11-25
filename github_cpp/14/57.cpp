

#include <iostream>
#include <vector>

using namespace std;










void countingSort(vector<vector <int>>& v, int n, int d) {

    int count[10] = {0};
    vector <int> temp;

    
    
	
	
	for (int c_i = 0; c_i < n; c_i++) {
    	count[v[c_i][d]]++;
    	cout << "count[v[c_i][d]] " << count[v[c_i][d]] << endl;
    }
    
    
    for (int c_j = 1; c_j < 10; c_j++) {
        count[c_j] += count[c_j-1];
        cout << "count[c_j] " << count[c_j] << endl;
    }
    
    for (int c_k = 0; c_k < n; c_k++) {
    	
    	
    }


    
    
 
    
}


void radixSort(vector<vector <int>>& v, int n) {

	for (int digit = 0; digit < 10; digit++) {
		
		countingSort(v, n, digit);
	}

	
}


int main() {
	int size = 0, input;
	
	vector<vector <int>> vectorSet;

	
	vector<int> vectorSubSet;
	cin >> size;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> input;
			vectorSubSet.push_back(input);
		}
		vectorSet.push_back(vectorSubSet);
		vectorSubSet.erase(vectorSubSet.begin(), vectorSubSet.end());
	}

	radixSort(vectorSet, size);

}
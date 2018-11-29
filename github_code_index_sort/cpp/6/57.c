/*

Radix Sort

About Radix:
Sorting algorithm for numbers by using the digits of the set of numbers. Relys on Counting Sort as a subroutine to sort the values. 

Copyright @Mark renzo Santiago

Running Time: O(d*(n+b))

*/

#include <iostream>
#include <vector>

using namespace std;

// void printSet(int output[10], int n) {
// 	for (int print_i = 0; print_i < n; print_i++) {
// 		cout << output[print_i] << ";";
// 	}
// 	cout << endl;
// }

/*

	Counting sort is the subroutine used to actually sort the values
	Counting sort is a stable sorting algorithm

*/

void countingSort(vector<vector <int>>& v, int n, int d) {

    int count[10] = {0};
    vector <int> temp;

    // store the count of each value into a count array
    /* 
    	 0 1 2 3 4 5 6 7 8 9
    EX: [                   ]
	*/
	// increment count array with the number of instances of the value
	// count array will be used as a key value hash table
	for (int c_i = 0; c_i < n; c_i++) {
    	count[v[c_i][d]]++;
    	cout << "count[v[c_i][d]] " << count[v[c_i][d]] << endl;
    }
    // find the sum of the current index and the previous sums
    // calculates the sum of the previous array values
    for (int c_j = 1; c_j < 10; c_j++) {
        count[c_j] += count[c_j-1];
        cout << "count[c_j] " << count[c_j] << endl;
    }
    // Build the output array
    for (int c_k = 0; c_k < n; c_k++) {
    	// v[c_k].swap(v[count[v[c_k][d]]]);
    	// count[c_k]--;
    }


    // Sort values into respective index while decreasing the count by 1
    // for (int c_k = 0; c_k < n; c_k++) {
 
    // }
}

// 
void radixSort(vector<vector <int>>& v, int n) {

	for (int digit = 0; digit < 10; digit++) {
		// stable sorting algorithm called as a subroutine to sort the digits 
		countingSort(v, n, digit);
	}

	
}


int main() {
	int size = 0, input;
	// Create the vector set that contains the vector of vectors
	vector<vector <int>> vectorSet;

	// the subset will be each vector set within the main vector
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
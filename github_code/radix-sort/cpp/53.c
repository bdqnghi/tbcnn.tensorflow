#include "header.hpp"

using namespace std;

#define N 10
#define M 1000

#define base 10

void countingSort(vector<int> *Aptr, int d) {
	vector<int> &A = *Aptr;
	vector<int> aux(A.size(), 0);				// aux array to store intermediate values
	vector<int> countArray(base, 0);		// count array of size base
		
	int pd = pow(base,d);

	// get count position for the number
	for (int i=0; i<A.size(); ++i) {
		int digit =  (A[i]/pd) % base;		// extract the digit
		countArray[digit]++;
	}

	// get absolute position
	for (int i=1; i<base; ++i) {
		countArray[i] = countArray[i-1] + countArray[i];
	}

	for (int i=aux.size()-1; i>=0; --i) {
		int digit =  (A[i]/pd) % base;		// extract the digit
		aux[countArray[digit]] = A[i];		// store the number at, location corresponding to the digit
		countArray[digit]--;
	}

	// replace content of one vector to other
	A = aux;
}

void radixSort(vector<int> *Aptr) {
	vector<int> &A = *Aptr;
	int maxd = *max_element(A.begin(), A.end());

	int msd=0;
	while(maxd) {
		maxd /= 10;
		msd++;
	}

	for (int d=0; d<msd; ++d) {
		countingSort(&A, d);
	}
}

int main() {
	vector<int> A;
	default_random_engine seed((random_device())());

	for (int i=0; i<N; ++i) {
		int r = uniform_int_distribution<int>{0,M}(seed);
		A.emplace_back(r);
	}

	cout <<"Before Sorting : "<<endl;
	for (int i=0; i<A.size(); ++i) {	
		cout << A[i] << ", ";
	}
	cout << endl;

	radixSort(&A);	

	cout <<"After Sorting : "<<endl;
	for (int i=0; i<A.size(); ++i) {	
		cout << A[i] << ", ";
	}
	cout << endl;

}

#include<iostream>
#include<vector>
#include<chrono>
#include <thread>


const int bounds = 32767; // will make random numbers between 1 and bounds
const int m = 10; // number of trials for each run.
using namespace std;
using namespace std::chrono;

void vprint(const vector<int>&A); //  prints vector for testing
vector<int> makeranv(const int &size); // takes in size, makes a vector of random ints from 1-bounds, returns that vector.
void INSERTION_SORT(vector<int> &A); // INSERTION-SORT
void MERGE_SORT(vector<int> &A, int p, int r); // MERGE-SORT
void MERGE(vector<int> &A, int p, int q, int r);
void QUICK_SORT(vector<int> &A, int p, int r); // QUICK-SORT 
int PARTITION(vector<int> &A, int p, int r);


int main(){

	vector<vector<int>> A, run1, run2, run3; //run1=ALG1, etc...
	vector<vector<double>>  run1T, run2T, run3T;// idk why but i had an issue using a vector of vectors for this, got confused so just defaulted to 2d array
	vector<int> temp; // used to store value of current run
	vector<double> tempV; // to store a list of times for the current run
	vector<double>run1Tavg, run2Tavg, run3Tavg;
	duration<double, std::milli> time; // total time in milliseconds
	high_resolution_clock::time_point t1; // start time
	high_resolution_clock::time_point t2; // end time



	for (size_t i = 5000; i <= 100000; i += 5000) // initializing all the test cases
	{
		A.push_back(makeranv(i));
	}

	run1 = run2 = run3 = A; // creating 3 instances of test cases, so all algorithms have same input

	cout << "INSERT-SORT BEGIN" << endl;
	for (size_t i = 0; i < run1.size(); i++) // run1/Insertion-Sort
	{
		cout << "run " << i + 1 << " " << endl;
		for (size_t j = 0; j < m; j++)
		{
			temp = run1[i];

			t1 = high_resolution_clock::now();

			INSERTION_SORT(temp);

			t2 = high_resolution_clock::now();

			time = t2 - t1;
			tempV.push_back(time.count());
		}
		run1T.push_back(tempV);
		tempV.clear();
	}
	cout << "INSERTION -SORT END, MERGE-SORT BEGIN" << endl;


	for (size_t i = 0; i < run2.size(); i++) // run2/Merge-Sort
	{
		cout << "run " << i + 1 << endl;
		for (size_t j = 0; j < m; j++)
		{
			temp = run2[i];

			t1 = high_resolution_clock::now();

			MERGE_SORT(temp, 0, temp.size() - 1);

			t2 = high_resolution_clock::now();

			time = t2 - t1;
			tempV.push_back(time.count());
			//vprint(temp);
		}
		run2T.push_back(tempV);
		tempV.clear();

	}



	cout << "MERGE-SORT END, QUICK-SORT BEGIN" << endl;
	for (size_t i = 0; i < run3.size(); i++) // run2/Quick-Sort
	{
		cout << "run " << i + 1 << endl;
		for (size_t j = 0; j < m; j++)
		{
			temp = run3[i];

			t1 = high_resolution_clock::now();

			QUICK_SORT(temp, 0, temp.size() - 1);

			t2 = high_resolution_clock::now();

			time = t2 - t1;
			tempV.push_back(time.count());
			//vprint(temp);
		}
		run3T.push_back(tempV);
		tempV.clear();
	}

	cout << "ALG3 END" << endl;

	// setting all to zero for later calculations
	for (size_t i = 0; i < A.size(); i++)
	{
		run1Tavg.push_back(0);
		run2Tavg.push_back(0);
		run3Tavg.push_back(0);
	}

	for (size_t i = 0; i < run1.size(); i++) // calulating averge RT for run1/insterion-sort
	{
		for (size_t j = 0; j < m; j++)
		{
			run1Tavg[i] += run1T[i][j];
		}
		run1Tavg[i] /= m;
	}
	for (size_t i = 0; i < run2.size(); i++) // merge-sort average rt
	{
		for (size_t j = 0; j < m; j++)
		{
			run2Tavg[i] += run2T[i][j];
		}
		run2Tavg[i] /= m;
	}
	for (size_t i = 0; i < run3.size(); i++)  // quick-sort avg rt
	{
		for (size_t j = 0; j < m; j++)
		{
			run3Tavg[i] += run3T[i][j];
		}
		run3Tavg[i] /= m;
	}
	for (size_t i = 0; i < run1.size(); i++) // output
	{
		cout << run1Tavg[i] << " ";
	}cout << endl;
	for (size_t i = 0; i < run2.size(); i++) // output
	{
		cout << run2Tavg[i] << " ";
	}cout << endl;
	for (size_t i = 0; i < run3.size(); i++) //output
	{
		cout << run3Tavg[i] << " ";
	}cout << endl;

	return 0;

}
void vprint(const vector<int>&A){ // prints vector
	for (size_t i = 0; i < A.size(); i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
}
vector<int> makeranv(const int &size){ // takes in size and makes a random vecotr of ints fro 1-bounds of that size, returns 
	// that vector
	vector<int> V;
	for (int i = 0; i < size; i++)
	{
		V.push_back(rand() % bounds + 1);
	}

	return V;
}
void INSERTION_SORT(vector<int> &A){ //  INSERTION-SORT

	int key;
	int i = 0;
	for (size_t j = 0; j < A.size(); j++){
		key = A[j];
		i = j - 1;
		while (i >= 0 && A[i] > key)
		{
			A[i + 1] = A[i];

			i--;
		}

		A[i + 1] = key;
	}
}
void MERGE_SORT(vector<int> &A, int p, int r){ // MEGRE-SORT
	int q;
	if (p<r){
		q = (p + r) / 2;
		MERGE_SORT(A, p, q);
		MERGE_SORT(A, q + 1, r);
		MERGE(A, p, q, r);
	}
}
void MERGE(vector<int> &A, int p, int q, int r){
	int n1 = q - p + 1;
	int n2 = r - q;
	int i, j, k;
	i = j = k = 0;
	vector<int> L, R;


	for (; i < n1; i++)
	{
		L.push_back(A[p + i]);
	}

	for (; j < n2; j++){

		R.push_back(A[q + j + 1]);
	}

	L.push_back(INT_MAX);
	R.push_back(INT_MAX);
	i = j = k = 0;
	for (k = p; k <= r; k++)
	{
		if (L[i] <= R[j]){
			A[k] = L[i];
			i++;
		}
		else{
			A[k] = R[j];
			j++;
		}
	}
}
void QUICK_SORT(vector<int> &A, int p, int r){ // QUICK-SORT
	if (p<r){
		int q = PARTITION(A, p, r);
		QUICK_SORT(A, p, q - 1);
		QUICK_SORT(A, q, r);
	}
}
int PARTITION(vector<int> &A, int p, int r){ // returns int q

	int x = A[r];
	int temp;
	int i = p - 1;

	for (int j = p; j < r; j++)
	{
		if (A[j] <= x){

			i++;

			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}


	}

	temp = A[r];
	A[r] = A[i + 1];
	A[i + 1] = temp;

	return i + 1;

}
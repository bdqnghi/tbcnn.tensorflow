// insertionsort.cpp

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// insertion sort
void ins_sort(vector<int> & v)
{
	int i, j, elem;
	int n = v.size();

	for (i = 1; i < n; i++)
   {	
		for (elem = v[i], j = i-1; j >=0 and elem < v[j]; j--)
   	{
			v[j+1] = v[j];
		}
		v[j+1] = elem;
	}
}

// main program
int main()
{
	srand(time(0)); // initialize random number generator
	int s; // initialize input size

	cin >> s;

	vector<int> v(s); // initialize vector with user input size
	
	// randomize numbers
	for(int i=0; i < v.size(); ++i)
	{
		v[i] = rand() % 1000001;
	}

	ins_sort(v); // bubble sort;

	for(int i=0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
	}
}

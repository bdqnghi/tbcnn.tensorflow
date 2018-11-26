// selectionsort.cpp

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// selection sort
void sel_sort(vector<int> & v)
{
	int i, j;
	int n = v.size();

	for (i = 0; i < n-1; i++)
	{
		for (j = i+1; j < n; j++)
		{
			if (v[i] > v[j])
			{
				swap(v[i], v[j]);
			}
		}
	}
}

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

	sel_sort(v); // bubble sort;

	for(int i=0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
	}
}

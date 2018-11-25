

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;


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


int main()
{
	srand(time(0)); 
	int s; 

	cin >> s;

	vector<int> v(s); 
	
	
	for(int i=0; i < v.size(); ++i)
	{
		v[i] = rand() % 1000001;
	}

	ins_sort(v); 

	for(int i=0; i < v.size(); ++i)
	{
		cout << v[i] << endl;
	}
}

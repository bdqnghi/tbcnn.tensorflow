   

							//Insertion  sort 
/*
			worst case time complexity --> O(n^2)
			best case and avg. case time complexity --> O(n^2)
			worst case space complexity --> O(n^2)(total) , O(1) auxillary
*/
	#include <iostream>
	#include <valarray>
	#include <vector>
	#include <cmath>
	#include <algorithm>
	using namespace std;
	void print(vector<int> a)
	{
		for(int i=0 ; i<a.size() ; i++)
			cout << a[i] << " ";
		cout << endl;
	}
	void insertion_sort(vector<int> &a)
	{
		int hole;
		for(int i=1 ; i<a.size() ; i++)
		{
			int val = a[i];
			hole = i;
			while(hole > 0 && a[hole-1] > val)
			{
				a[hole] =  a[hole-1];
				hole = hole -1;
			}
			a[hole] = val;
		}
	}
	int main()
	{
			vector<int> a ={9,43,2,3,4,6,4,23,1,3,4,56};
			insertion_sort(a);
			print(a);
			return 0;
	}
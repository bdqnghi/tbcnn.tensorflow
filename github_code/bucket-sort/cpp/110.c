#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

template <typename T>
void bucket_sort(vector<T> & vec);

int main(int argc, char * argv[])
{
	vector<int> a;
	for(int i = 0 ; i<100; i++)
	{
		int f = rand()%1000;
		cout << f << endl;
		a.push_back(f);
	}
	// cout << endl;
	// for(int i = 0 ; i<100; i++)
	// {
	// 	cout << a[i] << " ";
	// }
		
	// cout << endl;
	bucket_sort(a);
	for(int i = 0 ; i<100; i++)
	{
		cout << a[i] << " ";
	}

  return 0;
}

// bucket sort an array
// find range of elements [max-min] and then calcualte the number of buckets to make depending on range/size
//
template <typename T>
void bucket_sort(vector<T> & vec)
{
	T min = 0;
	for(int i =0;i<vec.size();i++)
	{
		if(vec[i] < min)
		{
			min = vec[i];
		}
	}//find min element

	T max = 0;
	for(int i =0;i<vec.size();i++)
	{
		if(vec[i] > min)
		{
			min = vec[i];
		}
	}//find max element

	//calcualte range
	T range = max-min;


	//make no of buckets = sqrt(range)
	int num_buckets  = ceil(sqrt(abs(max-min)));


	//making buckets
	vector<vector<T>> buckets (num_buckets);
	
	//run through unsorted and insert
	for(int i = 0; i < vec.size(); ++i)
	{
		buckets[abs(vec[i]-min)/sqrt(range)].push_back(vec[i]); 	//place element at |element-min|/sqrt(range)
	}


	//sort all inner vectors
	for(int i =0;i<buckets.size();i++)
	{
		sort(buckets[i].begin(),buckets[i].end());
	}


	//overwrite and return
	int place = 0;
	for(int i =0;i<buckets.size();++i)
	{
		auto j = buckets[i].begin();
		while(j!=buckets[i].end())
		{
			vec[place] = *j;
			++place;
			++j;
		}
	}
}
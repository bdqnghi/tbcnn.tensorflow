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
	
	
	
	
	
		
	
	bucket_sort(a);
	for(int i = 0 ; i<100; i++)
	{
		cout << a[i] << " ";
	}

  return 0;
}




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
	}

	T max = 0;
	for(int i =0;i<vec.size();i++)
	{
		if(vec[i] > min)
		{
			min = vec[i];
		}
	}

	
	T range = max-min;


	
	int num_buckets  = ceil(sqrt(abs(max-min)));


	
	vector<vector<T>> buckets (num_buckets);
	
	
	for(int i = 0; i < vec.size(); ++i)
	{
		buckets[abs(vec[i]-min)/sqrt(range)].push_back(vec[i]); 	
	}


	
	for(int i =0;i<buckets.size();i++)
	{
		sort(buckets[i].begin(),buckets[i].end());
	}


	
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
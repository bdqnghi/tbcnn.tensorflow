#include<iostream>
#include<conio.h>
#include<vector>
#include<algorithm>

using namespace std;

class InsertionSort 
{ 
	private:
		vector<int>& arr;
		bool more(int, int); 
		bool less(int, int); 

	public:
		InsertionSort(vector<int>&);
		virtual void sort(); 
};

InsertionSort:: InsertionSort(vector<int>& data):arr(data) { } 

bool InsertionSort::more(int value1, int value2) 
{
	return value1 > value2; 
}

bool InsertionSort::less(int value1, int value2) 
{
	return value1 < value2; 
}

void InsertionSort::sort()
{
	int size = arr.size();
	int temp, j;
	for (int i = 1; i < size; i++)
	{
		temp = arr[i];
		for (j = i; j > 0 && more(arr[j-1], temp); j--)
		{
			arr[j] = arr[j - 1];
		}
		arr[j] = temp;
	}
}

int main() 
{
    vector<int> data = { 9, 1, 8, 2, 7, 3, 6, 4, 5 };
	InsertionSort *bs = new InsertionSort(data);
	bs -> sort();
	for (int i = 0; i < data.size(); i++)
	    cout << data[i] << " ";
	return 0; 
}
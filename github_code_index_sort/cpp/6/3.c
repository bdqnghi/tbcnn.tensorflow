/*************************************************************************
	> File Name: radix.cpp
	> Author: weih
	> Mail: weihcao@163.com 
	> Created Time: Mon 08 Sep 2014 03:49:42 PM CST
 ************************************************************************/

#include <queue>
#include <vector>
#include <iostream>
#include <ctime>
using namespace std;
#define N 102400

void distribute(const vector<int> &v, queue<int> digitQueue[], int power)
{
	int i;
	for(i = 0; i < v.size(); i++)
		digitQueue[(v[i] / power) % 10].push(v[i]);
}

void collect(queue<int> digitQueue[], vector<int> &v)
{
	int i = 0, digit;
	for(digit = 0; digit < 10; ++digit)
		while( !digitQueue[digit].empty() )
		{
			v[i] = digitQueue[digit].front();
			digitQueue[digit].pop();
			++i;
		}
}

//利用基数排序对v排序，v中每个整数都是d位数
void radixSort(vector<int> &v, int d)
{
	int i;
	int power = 1;
	queue<int> digitQueue[10];

	for(i = 1; i <= d; ++i)
	{
		distribute(v, digitQueue, power);
		collect(digitQueue, v);
		power *= 10;
	}
}
int main()
{
	vector<int> v;
	for(int i = 0; i < N; ++i)
		v.push_back( N - i);

	cout << "before : ";
	for(int i = 0; i < 20; ++i)
		cout << v[i] << " ";
	cout << "...";
	for(int i = N-21; i < N; ++i)
		cout << v[i] << " ";
	cout << endl;

	clock_t t1 = clock();
	radixSort(v, 6);
	clock_t t2 = clock();
	cout << "耗时："  << double(t2 -t1)/CLOCKS_PER_SEC << endl;

	cout << "after: ";
	for(int i = 0; i < 20; ++i)
		cout << v[i] << " ";
	cout << "...";
	for(int i = N-21; i < N; ++i)
		cout << v[i] << " ";
	cout << endl;

}

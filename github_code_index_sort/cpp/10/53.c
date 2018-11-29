#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <chrono>
using namespace std;

double LKG() {
	const int m=193723,a=7297,c=1000;
	int X;
	X=(a*X+c)%m;
	return(X);
}

void bucketSort(int arr[],int n)
{
	vector <int> b[1000];
	for (int i=0;i<n;i++)	b[arr[i]/100].push_back(arr[i]);
	for (int i=0;i<1000;i++)	sort(b[i].begin(),b[i].end());
	int index=0;
	for (int i=0;i<1000;i++)
	{
		for (int j=0;j<b[i].size();j++)	arr[index++]=b[i][j];
	}
}
int main()
{
	int N=1000;
	int arr[N]={};
	for (int i=0;i<N;i++) arr[i]=(int) LKG()%10000;
	for (int i = 0; i < N; i++) std::cout << arr[i] << "\n";
	auto start = std::chrono::high_resolution_clock::now();
	bucketSort(arr,N);
	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << "Sorted array is:\n";
	//for (int i = 0; i < N; i++) std::cout << arr[i] << "\n";
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << elapsed.count() << "\n";
    return 0;
}

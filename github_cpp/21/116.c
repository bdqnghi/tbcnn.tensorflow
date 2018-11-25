#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

void selectionsort(int a[],int N)
{
  for(int l=0;l<=N-2;l++)
  {
    int x=min_element((a+l),(a+N));
    swap(a[x],a[l]);
  }
}

int main() 
{
	vector<int> a(10);
	cout << "排序前：" << endl;
	for (int i = 0; i < 10; i++)
	{
		a[i] = rand();
		cout << a[i]<<endl;
	}
	selectionsort(a.data(),10);
	cout << "排序后：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] <<endl;
	}
	system("pause");
	return 0;
}

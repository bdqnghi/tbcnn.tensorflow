#include <iostream>
using namespace std;

int rodCutting(int* price,int n)
{
	if(n<=0)
		return 0;

	int max_val=INT_MIN;

	//starting from length 1
	for (int i = 0; i < n; ++i)
	{
		max_val=max(max_val,price[i]+rodCutting(n-i-1));
	}

	return max_val;
}


int rodCuttingDP(int* price,int n)
{
	int val[n+1];
	val[0]=0;

	for (int i = 1; i <= n; ++i)
	{
		int max_val=INT_MIN;
		for (int j = 0; j < i; ++j)
		{
			//subtracting a length from i which is j,then automatically price of j is added
			max_val=max(max_val,price[j]+val[i-j-1]);
		}

		val[i]=max_val;
	}

	return val[n];
}

int main()
{

	return 0;
}
/*Given a rod of length n inches and an array of prices that contains prices of

all pieces of size smaller than n. Determine the maximum value obtainable

by cutting up the rod and selling the pieces.*/

#include <iostream>
#include <limits.h>	 //INT_MIN
#include <algorithm> //std::max

int cutRod(int* price, int n)
{
	int table[n+1],temp;		//table [n+1] is for storing the maximum price of pieces in bottom up approach
	table[0]=0;		
	for(int i=1; i<n+1; i++)
	{
		temp= INT_MIN;
		for(int j=0; j<i/2+1; j++)
			temp= std::max(temp,price[i-j-1]+table[j]);
		table[i]=temp;
	}
	return table[n];
}

int main()
{
	int l;
	std::cin>>l;
	int a[l];
	for (int i = 0; i < l; ++i)
	{
		std::cin>>a[i];
	}
	
	std::cout<<cutRod(a,l);
	return 0;
}

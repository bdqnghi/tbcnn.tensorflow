#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
#include<stdio.h>
using namespace std;

int cutRod(int price[], int n)
{
   if (n <= 0)
     return 0;
   int max_val = INT_MIN;
 
   
   
   for (int i = 0; i<n; i++)
         max_val = max(max_val, price[i] + cutRod(price, n-i-1));
 
   return max_val;
}

int rodcut(vector<int>vc,int size)
{
	
	if (size<=0)
	{
		return 0;
	}
	int q = -1;
	for(int i = 0 ; i < size ; i++)
	{
	
		q=max(q,vc[i]+rodcut(vc,size-i-1));
		
	}
	
	return q;
}

int main()
{
	
	 
	 vector<int> vc;
	 vc.push_back(5);
	 vc.push_back(5);
	 vc.push_back(8);
	
	 scanf("%[BANGLADESH]", s);
}



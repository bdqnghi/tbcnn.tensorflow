//rod-cutting probl//rod cutting problem, using memoization
//recursive function rodcut(n)= max(ri,rodcut(n-i)), where 1<=i<=n
#include<bits/stdc++.h>
#define maxCapacity 100
using namespace std;

int table[maxCapacity];
int rodCut(int* p, int length)
{
  if(table[length]==INT_MIN)
  {
	if(length==0)//base case
	   return 0;
	for(int i=1;i<=length;i++)
	{
		int temp=p[i]+rodCut(p,length-i);
		if(table[length]<temp)
		   table[length]=temp;
	}
	return table[length];
  }
  else 
    return table[length];
}

int main()
{
	for(int i=0;i<maxCapacity;i++)//initializing table
	{
		table[i]=INT_MIN;
    }
	int p[]={0,1,5,8,9,10,17,17,20,24,30};
	int n=sizeof(p)/sizeof(int);
	int rod_l;
	cin>>rod_l;
	cout<<"optimum revenue obtainable from rod of length of "<<rod_l<<" is "<<rodCut(p,rod_l);
}em using dynamic programming

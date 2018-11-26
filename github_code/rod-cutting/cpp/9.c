
using namespace std;

#include <map>
#include <numeric>
#include <string>
#include <functional>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <string.h>

#define fr(i,n) for(i=0;i<n;i++)

typedef vector<int> vi;
typedef vector<long long int > vll;
typedef long long int ll;
typedef vector<unsigned long long int > vull;
typedef unsigned long long int ull;
int max(int a,int b)
{
	if(a>b)
		return a;
	else 
		return b;
}
int rodcutter(int n,vi &pr , vi &rate )
{
	int i,q;
	rate[0]=0;
	for(i=1;i<=n;i++)
	{	q=-1;
		for(int j=1;j<=i;j++)
		{
			q = max(q,(pr[j]+rate[i-j]));
		}
		rate[i] = q ;
	}
	return rate[n];
}


int main ()
{
	int i,j,k,l,n,x,ans,nmbr;
	vi pr(1000);
	vi rate(1000);
    
	cin>>nmbr>>n;
	for(i=1;i<=nmbr;i++)
	{
		cin>>x;
		pr[i]=x;
	}
	
	ans=rodcutter(n,pr,rate);
	cout<<ans<<endl;
		return 0;
}

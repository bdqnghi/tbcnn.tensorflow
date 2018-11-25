#include<bits/stdc++.h>
using namespace std;

int max(int x,int y,int z)
{
	return max(max(x,y),max(y,z));
}
int function_rec(int a[],int n)
{
   
   if(n<0)
   	return 0;
    int res=0;
	for(int i=0;i<n;i++)
	{
		res=max(res,a[i]+function_rec(a,n-i-1));
	}
  return res;
}


int dp_function(int l,int a[])
{
  
  int dp[l+1];
  dp[0]=0;

  for(int i=1;i<=l;i++)
  { int max_val=INT_MIN;
  	for(int j=0;j<i;j++)
  		max_val=max(max_val,dp[i-j-1]+a[j]);
     dp[i]=max_val;
  }

  return dp[l];
}

int main()
{
	int l;
	cin>>l;
	int a[l];

	for(int i=0;i<l;i++)
        cin>>a[i];
   cout<<dp_function(l,a)<<endl;
   return 0;
}


